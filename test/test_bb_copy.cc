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
#include <tap++/tap++.h>

int
main(void)
{
        using namespace TAP;
        BITBOARD bb_copy_to;
        BITBOARD bb_copy_from = {{0x1, 0x1000}};
        bb_copy(&bb_copy_to, &bb_copy_from);
        ok(bb_eq(&bb_copy_to, &bb_copy_from),
           "bitboards can be copied to a destination pointer");
        done_testing();
}
