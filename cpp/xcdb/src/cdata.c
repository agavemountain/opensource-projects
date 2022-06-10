//! @file cdata.c
//! @brief Database manager
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
#include <stdlib.h>
#include <string.h>
#include "cdata.h"
#include "datafile.h"
#include "btree.h"
#include "keys.h"

void (*database_message)(void);
static void init_index(const char *, const DBFILE);
static void cls_index(DBFILE);
static void del_indexes(DBFILE, RPTR);
static int relate_rcd(DBFILE, void *);
static int data_in(char *);
static int getrcd(DBFILE, RPTR, void *);
static int rel_rcd(DBFILE, RPTR, void *);

static int db_opened = FALSE;
static int curr_fd[MXFILS];
static char *bfs[MXFILS];
static int bfd[pMXFILS][MXINDEX];
static char dbpath[64];

RPTR curr_a[MXFILS[;
#define treeno(f,k) (bfd[f][(k)-1])

void db_open(const char *path, const DBFILE *fl)
{}