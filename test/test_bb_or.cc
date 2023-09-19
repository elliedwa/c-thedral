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
        plan(4);
        BITBOARD or1_expected = {{1, 1}};
        BITBOARD or1_got;
        BITBOARD or1_bb_lhs = {{0, 1}};
        BITBOARD or1_bb_rhs = {{1, 0}};
        bb_or(&or1_got, &or1_bb_lhs, &or1_bb_rhs);
        ok(bb_eq(&or1_got, &or1_expected),
           "boards with no overlap return all bits set in either "
           "board");

        BITBOARD or2_expected = {{1, 1}};
        BITBOARD or2_got;
        BITBOARD or2_bb_lhs = {{0, 1}};
        BITBOARD or2_bb_rhs = {{1, 1}};
        bb_or(&or2_got, &or2_bb_lhs, &or2_bb_rhs);
        ok(bb_eq(&or2_got, &or2_expected),
           "boards with some overlap return all bits set in either "
           "board");

        BITBOARD or3_expected = {{0xffffffffffffULL, 0xffffffffffffULL << 16}};
        BITBOARD or3_got;
        BITBOARD or3_bb_lhs = {{0xff0ff0ff0ff0ULL, 0xff0ff0ff0ff0ULL << 16}};
        BITBOARD or3_bb_rhs = {{0x0ff0ff0ff0ffULL, 0xf0ff0ff0ff0fULL << 16}};
        bb_or(&or3_got, &or3_bb_lhs, &or3_bb_rhs);
        ok(bb_eq(&or3_got, &or3_expected),
           "operation works in more complex states");

        BITBOARD or4_expected = {
            {(UINT64_MAX >> 8) | (1ULL << 62), UINT64_MAX}};
        BITBOARD or4_got;
        BITBOARD or4_bb_lhs = {{UINT64_MAX >> 8, UINT64_MAX}};
        BITBOARD or4_bb_rhs = {{1ULL << 62, 1ULL << 62}};
        bb_or(&or4_got, &or4_bb_lhs, &or4_bb_rhs);
        ok(bb_eq(&or4_got, &or4_expected),
           "operation works in the higher bits");
}
