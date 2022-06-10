//! @file datafile.h
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
#ifndef _DATAFILE_H_
#define _DATAFILE_H_

//! \brief Create a data file
//!
//! This function is used to create a data file and is called from dbinit.c when the
//! files for the database are initialized.  The name pointer points to the DOS file name of the 
//! data file.  The len integer is the file's record length;
//!
//! \param name     file name
//! \param len      file length
void file_create(char *name, int len);

//! \brief open data file
//!
//! This function opens an existing data file, one that was previously created by
//! file_create, and returns a logical file handle that cdata uses for subsequent calls
//! to data file functions.  If the file does not exist, the function returns ERROR.
//!
//! \param name     file name
//!
//! \returns
//! \retval ERROR   ERROR is returned if the file does not exist or cannot be opened.
int file_open(char *);

//! \brief Close data file
//!
//! This function closes a data file.  You pass in the logical file handle that the
//! file_open function returned.
void file_close(int);

//! This function adds a record to the data file, writing it in the next available record
//! space in the file.  It will write the record either at the end of the file or, 
//! if records have been deleted from the file, into a record position that was formerlyh occupied by a
//! since deleted record.
//!
//! \returns
//! The RPTR return value is a typedef in cdata.h.  It will be either an integer or a long
//! integer, and it will represent the logical record position within the file that was
//! assigned to the record.  The RPTR value is relative to one.
RPTR new_record(int, void *);

//! \brief Get a record
//!
//! This function retrieves a record that was previously stored in the data file.  The RPTR
//! rcdno paramter is the logical record number where the record is known to be stored.  The 
//! bf pointer points to the buffer into which the record will be read.
int get_record(int, RPTR, void *);

//! \brief Put record
//!
//! This function rewrites a record to th efile and is used when the record has been changed.
//! The RPTR rcdno parameter is the logical record number where the record is to be stored.
//! The bf pointer points to the buffer from whcih the record will be written.
int put_record(int, RPTR, void *);

//! \brief Delete record
//!
//! This function deletes the record located at hte logcial record position rcdno.  The record
//! space is placed into a linked list for the file so that a later record addition can reuse
//! the space.
int delete_record(int, RPTR);

//! \brief file header
typedef struct fdhr {
    RPTR first_record;
    RPTR next_record;
    int record_length;
} FHEADER;

#endif
