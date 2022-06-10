//! @file sys.h
//! @brief System Subroutines
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
#ifndef _SYS_H_
#define _SYS_H_

//! \brief Returns a character from the keyboard
//!
//! This function returns a character from the keyboard without
//! the usual keyuboard enhancements included when the standard
//! C function getchar is used.  It also handles the translation of
//! function keys into the integer values as defined in keys.h
//!
//! \returns
//! This function returns the key value
int get_char(void);

void put_char(int c);

void clear_screen(void);

void cursor(int x, int y);

#endif