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

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"


/*
 * Happy Buckling Keyboard(IBM Model M mod)
 *
 * Pin usage:
 *   COL: PD0-7
 *   ROW: PB0-7, PF4-7
 */

#if (MATRIX_COLS > 16)
#   error "MATRIX_COLS must not exceed 16"
#endif
#if (MATRIX_ROWS > 255)
#   error "MATRIX_ROWS must not exceed 255"
#endif


#ifndef DEBOUNCE
#   define DEBOUNCE	0
#endif
static uint8_t debouncing = DEBOUNCE;

#define READ_DELAY 50

// matrix state buffer(1:on, 0:off)
#if (MATRIX_COLS <= 8)
static uint8_t *matrix;
static uint8_t *matrix_prev;
static uint8_t _matrix0[MATRIX_ROWS];
static uint8_t _matrix1[MATRIX_ROWS];
#else
static uint16_t *matrix;
static uint16_t *matrix_prev;
static uint16_t _matrix0[MATRIX_ROWS];
static uint16_t _matrix1[MATRIX_ROWS];
#endif

static uint8_t read_col(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

static char flip;

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
    print_enable = true;
    debug_enable = false;
    debug_matrix = false;
    debug_keyboard = false;
    debug_mouse = false;
    print("debug enabled.\n");

    // JTAG disable for PORT F. write JTD bit twice within four cycles.
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);

    // initialize rows
    unselect_rows();

    // initialize columns to input with pull-up(DDR:0, PORT:1)
    DDRB  = 0x00;
    PORTB = 0xff;
    DDRC  = 0x00;
    PORTC = 0xff;
    DDRD  = 0x00;
    PORTD = 0xFF;
    DDRF  = 0x00;
    PORTF = 0xff;

    flip = false;

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) _matrix0[i] = 0x00;
    for (uint8_t i=0; i < MATRIX_ROWS; i++) _matrix1[i] = 0x00;
    matrix = _matrix0;
    matrix_prev = _matrix1;
}


uint8_t matrix_scan(void)
{
    _delay_us(1);
    if (!debouncing) {
        uint8_t *tmp = matrix_prev;
        matrix_prev = matrix;
        matrix = tmp;
    }
    matrix[0] = ~(PINB | 0xc0);
    matrix[1] = ~(PINC | 0xc0);
    matrix[2] = ~(PIND | 0xc0);
    matrix[3] = ~(PINF);
    matrix[4] = (matrix[3] >> 6) & 0x03;
    matrix[3] &= 0x3f;
    return 1;
    /*for (uint8_t i = 0; i < matrix_cols(); i++){
        if (PINB & (1<<i) ){
            matrix[0] &= ~(1 << i);   
        } else { 
            matrix[0] |= 1 << i;
        }
         _delay_us(READ_DELAY); 
        if (PINC & (1<<i) ){
            matrix[1] &= ~(1 << i);   
        } else {
            matrix[1] |= 1 << i;
        }
        _delay_us(READ_DELAY); 
        if (PIND & (1<<i) ){
            matrix[2] &= ~(1 << i);   
        } else {
            matrix[2] |= 1 << i;
        }
        _delay_us(READ_DELAY); 
        if (PINF & (1<<i) ){
            matrix[3] &= ~(1 << i);
        } else {
            matrix[3] |= 1 << i;
        }
         _delay_us(READ_DELAY);
    }
    
    if (PINF & (1<<6) ){
        matrix[4] &= ~(1 << 0);
    } else {
        matrix[4] |= 1 << 0;
    }

    if (PINF & (1<<7) ){
        matrix[4] &= ~(1 << 1);
    } else {
        matrix[4] |= 1 << 1;
    }
*/
    /*if(flip == true){

        matrix[2]
    }*/

    if (debouncing) {
        debouncing--;
    }

    return 1;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (matrix[i] != matrix_prev[i]) {
            return true;
        }
    }
    return false;
}

inline
bool matrix_has_ghost(void)
{
    return false;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1<<col));
}

inline
#if (MATRIX_COLS <= 8)
uint8_t matrix_get_row(uint8_t row)
#else
uint16_t matrix_get_row(uint8_t row)
#endif
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < matrix_rows(); row++) {
        phex(row); print(": ");
#if (MATRIX_COLS <= 8)
        pbin_reverse(matrix_get_row(row));
#else
        pbin_reverse16(matrix_get_row(row));
#endif
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
#if (MATRIX_COLS <= 8)
        count += bitpop(matrix[i]);
#else
        count += bitpop16(matrix[i]);
#endif
    }
    return count;
}

inline
static uint8_t read_col(void)
{
    return 0;// do nothing
}

inline
static void unselect_rows(void)
{
    // do nothing
}

inline
static void select_row(uint8_t row)
{
    // do nothing
}
