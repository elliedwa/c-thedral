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

#ifndef CTHEDRAL_PBB_H_
#define CTHEDRAL_PBB_H_

#include "cthedral/bitboard.h"

typedef BITBOARD PADDED_BITBOARD;
typedef BITBOARD_HALF PADDED_BITBOARD_HALF;
static const PADDED_BITBOARD_HALF PADDING_BITS = 0x40080100200400;
static const PADDED_BITBOARD_HALF OVERFLOW_BIT = (1ULL << 55);
static const PADDED_BITBOARD_HALF PADDED_ILLEGAL_MASK =
    PADDING_BITS | OVERFLOW_BIT;
static const PADDED_BITBOARD_HALF PADDED_PIECES_BITS = 0xff00000000000000;
static const PADDED_BITBOARD_HALF PADDED_OFFBOARD_MASK =
    PADDED_ILLEGAL_MASK | PADDED_PIECES_BITS;

PADDED_BITBOARD *pbb_shl(PADDED_BITBOARD *board);
BITBOARD_HALF pbb_half_remove_padding(PADDED_BITBOARD_HALF half);
BITBOARD pbb_remove_padding(PADDED_BITBOARD board);
bool pbb_validate(PADDED_BITBOARD board);
bool pbb_check_stop_bit(PADDED_BITBOARD board);

#endif
