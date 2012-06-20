/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_H
#define CONFIG_H

/* controller configuration */
#include "controller_teensy.h"

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0xBB00
#define MANUFACTURER    grapefrukt
#define PRODUCT         super fantastic cocktail arcade
#define DESCRIPTION     four player arcade controller


/* matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 6
/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST
/* Set 0 if need no debouncing */
#define DEBOUNCE    0


/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KB_LSHIFT) | MOD_BIT(KB_LCTRL) | MOD_BIT(KB_LALT) | MOD_BIT(KB_LGUI)) || \
    keyboard_report->mods == (MOD_BIT(KB_LALT) | MOD_BIT(KB_RALT)) \
)


/* mouse keys */
#ifdef MOUSEKEY_ENABLE
#   define MOUSEKEY_DELAY_TIME 128
#endif

#endif
