/*
 * Copyright 2023 Elliot C. Edwards
 *
 * c-thedral is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * c-thedral is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with c-thedral.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef CATHEDRAL_BITBOARD_H_
#define CATHEDRAL_BITBOARD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define NUM_ROWS 10
#define NUM_COLS 10
#define NUM_SQUARES (NUM_ROWS * NUM_COLS)
#define PADDED_ROW_LENGTH (NUM_COLS + 1)

typedef struct {
        uint64_t bb[2];
} BITBOARD;

typedef uint64_t BITBOARD_HALF;

static const BITBOARD_HALF PIECES_BITS = 0xfffc000000000000;

static const uint64_t ROW_MASK         = (1ULL << NUM_COLS) - 1;

BITBOARD bb_not(BITBOARD board);
void bb_and(BITBOARD *res, BITBOARD *lhs, BITBOARD *rhs);
void bb_or(BITBOARD *res, BITBOARD *lhs, BITBOARD *rhs);
void bb_xor(BITBOARD *res, BITBOARD *lhs, BITBOARD *rhs);
bool bb_empty(BITBOARD *board);
bool bb_eq(BITBOARD *lhs, BITBOARD *rhs);
bool bb_ne(BITBOARD *lhs, BITBOARD *rhs);

void bb_copy(BITBOARD *to, BITBOARD *from);

bool bb_is_placement(const BITBOARD *bb);

int bb_cmp(const void *lhs, const void *rhs);

void DEBUG_print_bitboard_hex(BITBOARD *b);
void DEBUG_print_bitboard_visual(BITBOARD *b);

#ifdef __cplusplus
}
#endif

#endif
