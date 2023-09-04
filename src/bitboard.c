/* Copyright 2023 Elliot C. Edwards

c-thedral is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

c-thedral is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with c-thedral.  If not, see <https://www.gnu.org/licenses/>. */

#include "cthedral/bitboard.h"

/* this really only works one shift at a time, but that's all we need */
BITBOARD
bb_shl(BITBOARD board)
{

        BITBOARD res = {{board.bb[0] << 1, board.bb[1] << 1}};
        if (res.bb[0] & OVERFLOW_BIT) {
                res.bb[0] ^=
                    OVERFLOW_BIT; /* remove the bit from first half... */
                res.bb[1] |= 1;   /*  ... and add it to second half */
        }
        return res;
}

BITBOARD
bb_not(BITBOARD board)
{
        BITBOARD res = {{~board.bb[0], ~board.bb[1]}};
        return res;
}

BITBOARD
bb_and(BITBOARD lhs, BITBOARD rhs)
{
        BITBOARD res = {{lhs.bb[0] & rhs.bb[0], lhs.bb[1] & rhs.bb[1]}};
        return res;
}

BITBOARD
bb_or(BITBOARD lhs, BITBOARD rhs)
{
        BITBOARD res = {{lhs.bb[0] | rhs.bb[0], lhs.bb[1] | rhs.bb[1]}};
        return res;
}

BITBOARD
bb_xor(BITBOARD lhs, BITBOARD rhs)
{
        BITBOARD res = {{lhs.bb[0] ^ rhs.bb[0], lhs.bb[1] ^ rhs.bb[1]}};
        return res;
}

bool
bb_empty(BITBOARD board)
{
        return (board.bb[0] || board.bb[1]);
}

bool
validate_padded_bitboard(PADDED_BITBOARD board)
{
        return !((board.bb[0] & PADDING_BITS) || (board.bb[1] & PADDING_BITS));
}

bool
check_stop_bit(PADDED_BITBOARD board)
{
        return (board.bb[1] & OVERFLOW_BIT);
}

BITBOARD_HALF
bb_half_remove_padding(PADDED_BITBOARD_HALF half)
{
        uint64_t res = 0;
        for (int r = 0; r < 5; r++) {
                res |= (half & (ROW_MASK << (r * PADDED_ROW_LENGTH))) >> r;
        }
        return res;
}

BITBOARD
bb_remove_padding(PADDED_BITBOARD board)
{
        BITBOARD res = {{0, 0}};
        res.bb[0]    = bb_half_remove_padding(board.bb[0]);
        res.bb[1]    = bb_half_remove_padding(board.bb[1]);
        return res;
}
void
DEBUG_print_bitboard_hex(BITBOARD b)
{
        printf("%.16lx|%.16lx\n", b.bb[0], b.bb[1]);
}
