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

#include <cthedral/bitboard.h>
#include <cthedral/pieces.h>
#include <cthedral/placement_gen.h>
#include <tap++/tap++.h>

int
main(void)
{
        using namespace TAP;
        BITBOARD bb1       = {{0, 0}};
        BITBOARD cathedral = {{0x400803802, 0}};
        BITBOARD cbit      = piece_bit(CATHEDRAL);
        bb_or(&bb1, &cathedral, &cbit);

        BITBOARD bb2    = {{0, 0}};
        BITBOARD tavern = {{0x1, 0}};
        BITBOARD ltbit  = piece_bit(LIGHT_TAVERN_1);
        bb_or(&bb2, &tavern, &ltbit);

        BITBOARD bb3            = {{0, 0}};
        BITBOARD tavern_shifted = {{0x1ULL << 6, 0}};
        BITBOARD ltshiftbit     = piece_bit(LIGHT_TAVERN_1);
        bb_or(&bb3, &tavern_shifted, &ltshiftbit);

        BITBOARD bb4         = {{0, 0}};
        BITBOARD tavern_dark = {{0x1, 0}};
        BITBOARD dtbit       = piece_bit(DARK_TAVERN_1);
        bb_or(&bb4, &tavern_dark, &dtbit);

        is(bb_cmp(&bb1, &bb1), 0, "equal bitboards return 0");
        is(bb_cmp(&bb1, &bb2), -1, "cathedral comes before light tavern");
        is(bb_cmp(&bb2, &bb3), -1, "piece in higher position comes later");
        is(bb_cmp(&bb3, &bb4), -1, "dark pieces are after light");

        done_testing();
}
