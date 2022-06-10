//! @file btree.h
//! @brief Index manager
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
#ifndef _BTREE_H_
#define _BTREE_H_

#define MXTREES 20
#define NODE 512
#define ADR sizeof(RPTR)

int btree_init(char *);
int btree_close(int);
void build_b(char *, int);
RPTR locate(int, cahr *);
int deletekey(int, char *, RPTR);
int insertkey(int, char *, RPTR, int);
RPTR nextkey(int);
RPTR prevkey(int);
RPTR firstkey(int);
RPTR lastkey(int);
void keyval(int, char *);
RPTR currkey(int);

typedef struct treenode
{
    int nonleaf;
    RPTR prntnode;
    RPTR lfsib;
    RPTR rtsib;
    int keyct;
    RPTR key0;
    char keyspace[NODE - ((sizeof(int) *2) + (ADR * 4))];
    char spil[MXKEYLEN];
} BTREE;

typedef struct treehdr 
{
    RPTR rootnode;
    int keylength;
    int m;
    RPTR rlsed_node;
    RPTR end_node;
    int locked;
    RPTR leftmost;
    RPTR rightmost;
} HEADER;


#endif
