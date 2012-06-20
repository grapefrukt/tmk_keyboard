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

/* 
 * Keymap for Macway mod
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "usb_keycodes.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "keymap.h"


/*
 * Layout: 59key
 * ,-----------------------------------------------------------.
 * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
 * |-----------------------------------------------------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]| BS  |
 * |-----------------------------------------------------------|
 * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn3|  '|Return  |
 * |-----------------------------------------------------------|
 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|Fn2|Shift     |
 * |-----------------------------------------------------------|
 * |Ctrl |   |Alt  |           Fn4             |Alt  |   |Fn1  |
 * `-----'   `---------------------------------------'   `-----'
 *
 * Matrix: 12x8
 *    |       0 |       1 |       2 |       3 |       4 |       5 |       6 |       7
 * ---+---------+---------+---------+---------+---------+---------+---------+---------
 *  0 |         |         | LCTRL   |         |         |         | RCTRL   |        
 *  1 |         | LSHIFT  |         |         |         |         | RSHIFT  |        
 *  2 |         | Tab     | Grave   | 1       | Q       | A       | Z       |        
 *  3 |         | Cpslck  |         | 2       | W       | S       | X       |        
 *  4 |         |         |         | 3       | E       | D       | C       |        
 *  5 | G       | T       | 5       | 4       | R       | F       | V       | B      
 *  6 |         | Bckspc  |         |         | Key*1   | Bckslsh | Enter   | Space  
 *  7 | H       | Y       | 6       | 7       | U       | J       | M       | N      
 *  8 |         | Rbrckt  | Equal   | 8       | I       | K       | Comma   |
 *  9 |         |         |         | 9       | O       | L       | Dot     |        
 *  A |         | Lbrckt  | Minus   | 0       | P       | Smcolon |         | Slash  
 *  B | LALT    |         |         |         |         |         |         | RALT   
 *  Key*1 This key locates between Equal and Backspace.
 *
 *  Original matrix here: http://geekhack.org/showthread.php?7767-Wireless-Model-M&p=133911&viewfull=1#post133911
 */
#define KEYMAP( \
    K00, K10, K20, K30, K40, K50, \
    K01, K11, K21, K31, K41, K51, \
    K02, K12, K22, K32, K42, K52, \
    K03, K13, K23, K33, K43, K53, \
    K04, K14, K24, K34, K44, K54 ) { \
    { KB_##K00, KB_##K10, KB_##K20, KB_##K30, KB_##K40, KB_##K50, }, \
    { KB_##K01, KB_##K11, KB_##K21, KB_##K31, KB_##K41, KB_##K51, }, \
    { KB_##K02, KB_##K12, KB_##K22, KB_##K32, KB_##K42, KB_##K52, }, \
    { KB_##K03, KB_##K13, KB_##K23, KB_##K33, KB_##K43, KB_##K53, }, \
    { KB_##K04, KB_##K14, KB_##K24, KB_##K34, KB_##K44, KB_##K54, }, \
}

#define KEYCODE(layer, row, col) (pgm_read_byte(&keymaps[(layer)][(row)][(col)]))


// Assign Fn key(0-7) to a layer to which switch with the Fn key pressed.
static const uint8_t PROGMEM fn_layer[] = {
    0,              // Fn0
    0,              // Fn1
    0,              // Fn2
    0,              // Fn3
    0,              // Fn4
    0,              // Fn5
    0,              // Fn6
    0               // Fn7
};

// Assign Fn key(0-7) to a keycode sent when release Fn key without use of the layer.
// See layer.c for details.
static const uint8_t PROGMEM fn_keycode[] = {
    KB_NO,          // Fn0
    KB_NO,          // Fn1
    KB_SLSH,        // Fn2
    KB_SCLN,        // Fn3
    KB_SPC,         // Fn4
    KB_NO,          // Fn5
    KB_NO,          // Fn6
    KB_NO           // Fn7
};

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]| BS  |
     * |-----------------------------------------------------------|
     * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn3|  '|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|Fn2|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |   |Alt  |           Fn4             |Alt  |   |Fn1  |
     * `-----'   `---------------------------------------'   `-----'
     */
    KEYMAP(0, 1, 2, 3, 4, 5, \
           0, 1, 2, 3, 4, 5, \
           0, 1, 2, 3, 4, 5, \
           0, 1, 2, 3, 4, 5, \
           0, 1, 2, 3, 4, 5  ),
};


uint8_t keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t col)
{
    return KEYCODE(layer, row, col);
}

uint8_t keymap_fn_layer(uint8_t fn_bits)
{
    return pgm_read_byte(&fn_layer[biton(fn_bits)]);
}

uint8_t keymap_fn_keycode(uint8_t fn_bits)
{
    return pgm_read_byte(&fn_keycode[(biton(fn_bits))]);
}
