//! @file sys.c
//! @brief System Subroutines
//! 
//! This file contains functions that are keyboard and screen drivers for
//! the PC with ANSI.SYS installed. 
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
#include <unistd.h>
#include <termios.h>
#include "keys.h"
#include "sys.h"
#include "cdata.h"

extern int FieldChar, screen_displayed;

//! getch is a function that doesn't exist outside DOS, 
//! especially in Linux.
char getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    printf("%c\n", buf);
    return buf;
 }

void put_char(int c)
{
    switch(c) {
        case FWD:
            printf("\033[C");
            break;
        case UP:
            printf("\033[A");
            break;
        default:
            putchar(c == ' ' ? FieldChar : c );
    }
    fflush(stdout);
}

void cursor(int x, int y)
{
    printf("\033[%02d;%02dH", y+1, x+1);
    fflush(stdout);
}

void clear_screen(void)
{
    screen_displayed=0;
    printf("\033[2J");
    fflush(stdout);
}

int get_char(void)
{
    int c;

    if ((c= getch()) == 0)
    {
        c = getch() | 128;
    }
    return c & 255;
}
