//! @file datafile.c
//! @brief data file management functions
//!
//! @copyright
//!
//!     This file is part of XCDB.
//!
//!     XCDB is free software: you can redistribute it and/or modify it under the terms
//!     of the GNU General Public License as published by the Free Software Foundation,
//!     either version 3 of the License, or (at your option) any later version.
//!
//!     XCDB is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
//!     without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//!     PURPOSE. See the GNU General Public License for more details.
//!
//!     You should have received a copy of the GNU General Public License along with XCDB.
//!     If not, see <https://www.gnu.org/licenses/>.
//!
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "cdata.h"
#include "datafile.h"

#define flocate(r, l) ((long)(sizeof(FHEADER) + (((r)-1) * (l))))

static FILE *fp[MXFILS];
FHEADER fh[MXFILS];

void file_create(char *name, int len)
{
    FILE *fp;
    FHEADER hd;

    remove(name);
    fp = fopen(name, "wb");
    hd.next_record = 1;
    hd.first_record = 0;
    hd.record_length = len;
    fwrite((char *)&hd, sizeof(hd), 1, fp);
    fclose(fp);
}

int file_open(char *name)
{
    int fno;

    for (fno = 0; fno < MXFILS; fno++)
    {
        if (fp[fno] == NULL)
            break;
    }

    if (fno == MXFILS)
    {
        return ERROR;
    }

    if ((fp[fno] = fopen(name, "rb+")) == NULL)
    {
        return ERROR;
    }

    fseek(fp[fno], 0L, SEEK_SET);
    fread((char *)&fh[fno], sizeof(FHEADER), 1, fp[fno]);

    return fno;
}

void file_close(int fno)
{
    fseek(fp[fno], 0L, SEEK_SET);
    fwrite((char *) &fh[fno], sizeof(FHEADER), 1, fp[fno]);
    fclose(fp[fno]);
    fp[fno] = NULL;
}

RPTR new_record(int fno, void *bf)
{
    RPTR rcdno;
    FHEADER *c;

    if (fh[fno].first_record)
    {
        rcdno = fh[fno].first_record;
        if ((c = malloc(fh[fno].record_length)) == NULL)
        {
            errno = D_OM;
            dberror();
        }
        get_record(fno, rcdno, c);
        fh[fno].first_record = c->next_record;
        free(c);
    }
    else
    {
        rcdno = fh[fno].next_record++;
    }
    put_record(fno, rcdno, bf);
    return rcdno;

}

int get_record(int fno, RPTR rcdno, void *bf)
{
    if (rcdno >= fh[fno].next_record)
    {
        return ERROR;
    }
    fseek(fp[fno], flocate(rcdno, fh[fno].record_length), SEEK_SET);
    fread(bf, fh[fno].record_length, 1, fp[fno]);
    return OK;
}

int put_record(int fno, RPTR rcdno, void *bf)
{
    if (rcdno > fh[fno].next_record)
    {
        return ERROR;
    }
    fseek(fp[fno], flocate(rcdno, fh[fno].record_length), SEEK_SET);
    fwrite(bf, fh[fno].record_length, 1, fp[fno]);
    return OK;
}

int delete_record(int fno, RPTR rcdno)
{
    FHEADER *bf;

    if (rcdno > fh[fno].next_record)
    {
        return ERROR;
    }
    if ((bf = (FHEADER *)malloc(fh[fno].record_length)) == NULL)
    {
        errno = D_OM;
        dberror();
    }

    memset(bf, '\0', fh[fno].record_length);
    bf->next_record = fh[fno].first_record;
    bf->first_record = -1;
    fh[fno].first_record = rcdno;
    put_record(fno, rcdno, bf);
    free(bf);
    return OK;
}
