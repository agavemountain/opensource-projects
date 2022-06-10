//! @file cdata.h
//! @brief The CDATA DBMS HEADER
//!
//! This file contains a set of #define statements that equate to 
//! global symbols to the function keys on the IBM PC keyboard.
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
#ifndef _CDATA_H_
#define _CDATA_H_

#include <stdio.h>

#define MXFILS  11
#define MXELE   100
#define MXINDEX 5
#define MXKEYLEN 80
#define MXCAT   3
#define NAMLEN  31

extern void (*database_message)(void);

#define ERROR -1
#define OK  0

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef long RPTR;

#ifndef APPLICATION_H
typedef int DBFILE;
typedef int ELEMENT;
#endif

/* schema as built for the application */
extern const char *dbfiles[];
extern const char *denames[];
extern const char *elmask[];
extern const char eltype[];
extern const int ellen[];
extern const ELEMENT *file_ele[];
extern const ELEMENT **index_ele[];

/* database prototypes */

/* CDATA API functions */
void db_open(const char *, const DBFILE *);
int add_rcd(DBFILE, void *);
int find_rcd(DBFILE, int, char, void *);
int verify_rcd(DBFILE, int, char *);
int first_rcd(DBFILE, int, void *);
int last_rcd(DBFILE, int, void *);
int next_rcd(DBFILE, int, void *);
int prev_rcd(DBFILE, int, void *);
int rtn_rcd(DBFILE, void *);
int del_rcd(DBFILE);
int curr_rcd(DBFILE, int, void *);
int seqrcd(DBFILE, void *);
void db_cls(void);
void dberror(void);
int rlen(DBFILE);
void init_rcd(DBFILE, void *);
void clrrcd(void *, const ELEMENT *);
int epos(ELEMENT, const ELEMENT *);
void rcd_fill(const void *, void *, const ELEMENT *, const ELEMENT *);

/* functions used by CDATA utility programs */
void build_index(char *, DBFILE);
int add_indexes(DBFILE, void *, RPTR);
DBFILE fileame(char *);
void name_cvt(char *, char *);
int ellist(int, char **, ELEMENT *);
void clist(FILE *, const ELEMENT *, const ELEMENT *, void *, const char *);
void test_eop(FILE *, const char *, const ELEMENT *);
void dblist(FILE *, DBFILE, int, const ELEMENT *);

// dbms error codes for errno return
enum dberrors {
    D_NF = 1,   // record not found
    D_PRIOR,    // no prior record for this request
    D_EOF,      // end of file
    D_BOF,      // beginning of file
    D_DUPL,     // primary key already exists
    D_OM,       // out of memory
    D_INDXC,    // index curruption
    D_IOERR,    // I/O error
};

#endif



