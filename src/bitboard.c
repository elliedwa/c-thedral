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

/*
 * The bitboard algorithms in c-thedral are adapted from those described in
 * "Using Bitboards for Move Generation in Shogi" by Reijer Grimbergen,
 * available at <https://www2.teu.ac.jp/gamelab/RESEARCH/ICGAJournal2007.pdf>
 */

#include "cthedral/bitboard.h"

bool
bb_empty(BITBOARD *board)
{
        return (board->bb[0] == 0) && (board->bb[1] == 0);
}

bool
bb_eq(BITBOARD *lhs, BITBOARD *rhs)
{
        return lhs->bb[0] == rhs->bb[0] && lhs->bb[1] == rhs->bb[1];
}

bool
bb_ne(BITBOARD *lhs, BITBOARD *rhs)
{
        return !bb_eq(lhs, rhs);
}

BITBOARD
bb_not(BITBOARD board)
{
        BITBOARD res = {{~board.bb[0], ~board.bb[1]}};
        return res;
}

void
bb_and(BITBOARD *res, BITBOARD *lhs, BITBOARD *rhs)
{
        res->bb[0] = lhs->bb[0] & rhs->bb[0];
        res->bb[1] = lhs->bb[1] & rhs->bb[1];
}
void
bb_or(BITBOARD *res, BITBOARD *lhs, BITBOARD *rhs)
{
        res->bb[0] = lhs->bb[0] | rhs->bb[0];
        res->bb[1] = lhs->bb[1] | rhs->bb[1];
}

void
bb_xor(BITBOARD *res, BITBOARD *lhs, BITBOARD *rhs)
{
        res->bb[0] = lhs->bb[0] ^ rhs->bb[0];
        res->bb[1] = lhs->bb[1] ^ rhs->bb[1];
}

void
bb_copy(BITBOARD *to, BITBOARD *from)
{
        to->bb[0] = from->bb[0];
        to->bb[1] = from->bb[1];
}
