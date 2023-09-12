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

#include "cthedral/pieces.h"
#include "cthedral/bitboard.h"
size_t WHOSE_PIECE[DARK_ACADEMY + 1] = {
    [LIGHT_TAVERN_1] = 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, [DARK_TAVERN_1] = 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

BITBOARD
piece_bit(enum piece p)
{
        BITBOARD_HALF b = 1ULL << (p + 49);
        BITBOARD bit = {{0, 0}};
        bit.bb[WHOSE_PIECE[p]] = b;

        return bit;
}
