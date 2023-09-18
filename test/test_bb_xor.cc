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
}
#include <tap++/tap++.h>

int
main(void)
{
        using namespace TAP;
        plan(4);

        BITBOARD xor1_expected = {{1, 1}};
        BITBOARD xor1_got;
        BITBOARD xor1_bb_lhs = {{0, 1}};
        BITBOARD xor1_bb_rhs = {{1, 0}};
        bb_xor(&xor1_got, &xor1_bb_lhs, &xor1_bb_rhs);
        ok(bb_eq(&xor1_got, &xor1_expected),
           "boards with no overlap return all bits set in either "
           "board");

        BITBOARD xor2_expected = {{1, 0}};
        BITBOARD xor2_got;
        BITBOARD xor2_bb_lhs = {{0, 1}};
        BITBOARD xor2_bb_rhs = {{1, 1}};
        bb_xor(&xor2_got, &xor2_bb_lhs, &xor2_bb_rhs);
        ok(bb_eq(&xor2_got, &xor2_expected),
           "boards with some overlap return only differing bits");

        BITBOARD xor3_expected = {{0xf0ff0ff0ff0fULL, 0x0ff0ff0ff0ffULL << 16}};
        BITBOARD xor3_got;
        BITBOARD xor3_bb_lhs = {{0xff0ff0ff0ff0ULL, 0xff0ff0ff0ff0ULL << 16}};
        BITBOARD xor3_bb_rhs = {{0x0ff0ff0ff0ffULL, 0xf0ff0ff0ff0fULL << 16}};
        bb_xor(&xor3_got, &xor3_bb_lhs, &xor3_bb_rhs);
        ok(bb_eq(&xor3_got, &xor3_expected),
           "operation works in more complex states");

        BITBOARD xor4_expected = {
            {(UINT64_MAX >> 8) ^ (1ULL << 62), UINT64_MAX ^ (1ULL << 62)}};
        BITBOARD xor4_got;
        BITBOARD xor4_bb_lhs = {{UINT64_MAX >> 8, UINT64_MAX}};
        BITBOARD xor4_bb_rhs = {{1ULL << 62, 1ULL << 62}};
        bb_xor(&xor4_got, &xor4_bb_lhs, &xor4_bb_rhs);
        ok(bb_eq(&xor4_got, &xor4_expected),
           "operation works in the higher bits");
}
