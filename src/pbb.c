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

#include "cthedral/pbb.h"

bool
pbb_validate(PADDED_BITBOARD board)
{
        return !((board.bb[0] & PADDING_BITS) || (board.bb[1] & PADDING_BITS));
}

bool
pbb_check_stop_bit(PADDED_BITBOARD board)
{
        return (board.bb[1] & OVERFLOW_BIT);
}

BITBOARD_HALF
pbb_half_remove_padding(PADDED_BITBOARD_HALF half)
{
        uint64_t res = 0;
        for (int r = 0; r < 5; r++) {
                res |= (half & (ROW_MASK << (r * PADDED_ROW_LENGTH))) >> r;
        }
        return res;
}

BITBOARD
pbb_remove_padding(PADDED_BITBOARD board)
{
        BITBOARD res = {{0, 0}};
        res.bb[0]    = pbb_half_remove_padding(board.bb[0]);
        res.bb[1]    = pbb_half_remove_padding(board.bb[1]);
        return res;
}

/* this really only works one shift at a time, but that's all we need */
PADDED_BITBOARD *
pbb_shl(PADDED_BITBOARD *board)
{

        board->bb[0] <<= 1;
        board->bb[1] <<= 1;
        if (board->bb[0] & OVERFLOW_BIT) {
                board->bb[0] ^=
                    OVERFLOW_BIT;  /* remove the bit from first half... */
                board->bb[1] |= 1; /*  ... and add it to second half */
        }
        return board;
}
