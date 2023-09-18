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

extern "C" {
#include <cthedral/bitboard.h>
#include <cthedral/placement_gen.h>
}
#include <tap++/tap++.h>

int
main(void)
{
        using namespace TAP;

        placement_array pa;
        generate_placement_array(&pa);
        is(sizeof(pa.bb) / sizeof(pa.bb[0]), PA_CAPACITY,
           "correct number of bitboards");
        is(sizeof(pa.bb), sizeof(BITBOARD) * PA_CAPACITY,
           "correct number of bitboards, tested another way");

        is(sizeof(pa.cathedral), sizeof(BITBOARD) * NUM_CATHEDRAL_PLACEMENTS,
           "pa union works (cathedral)");
        is(sizeof(pa.light), sizeof(BITBOARD) * NUM_PLAYER_PLACEMENTS,
           "pa union works (light)");
        is(sizeof(pa.dark), sizeof(BITBOARD) * NUM_PLAYER_PLACEMENTS,
           "pa union works (dark)");
        is(sizeof(pa.bb),
           sizeof(pa.cathedral) + sizeof(pa.light) + sizeof(pa.dark),
           "pa union works (sum of sizes)");
        done_testing();
}
