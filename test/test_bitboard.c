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
#include "tap.h"

int
main(void)
{
        plan(NO_PLAN);

        BITBOARD empty = {{0, 0}};
        ok(bb_empty(empty), "empty bitboards can be detected");
        BITBOARD not_empty = {{0, 1}};
        ok(!bb_empty(not_empty), "non-empty bitboards can also be detected");

        ok(bb_eq(empty, empty), "a bitboard equals itself");
        ok(bb_ne(empty, not_empty),
           "a bitboard does not equal some other bitboard");
        cmp_ok(bb_eq(empty, empty), "==", !bb_ne(empty, empty),
               "bb_eq and bb_ne are inverses of each other");

        done_testing();
}
