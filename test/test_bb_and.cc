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

        BITBOARD and1_expected = {{0, 0}};
        BITBOARD and1_got;
        BITBOARD and1_bb_lhs = {{0, 1}};
        BITBOARD and1_bb_rhs = {{1, 0}};
        bb_and(&and1_got, &and1_bb_lhs, &and1_bb_rhs);
        ok(bb_eq(&and1_got, &and1_expected),
           "boards with no overlap return empty board");

        BITBOARD and2_expected = {{0, 1}};
        BITBOARD and2_got;
        BITBOARD and2_bb_lhs = {{0, 1}};
        BITBOARD and2_bb_rhs = {{1, 1}};
        bb_and(&and2_got, &and2_bb_lhs, &and2_bb_rhs);
        ok(bb_eq(&and2_got, &and2_expected),
           "boards with some overlap return all common bits");

        BITBOARD and3_expected = {{0, 0x3c0c3}};
        BITBOARD and3_got;
        BITBOARD and3_bb_lhs = {{0, 0x3c0c3}};
        BITBOARD and3_bb_rhs = {{0, 0x3c0c3}};
        bb_and(&and3_got, &and3_bb_lhs, &and3_bb_rhs);
        ok(bb_eq(&and3_got, &and3_expected), "board & itself returns itself");

        BITBOARD and4_expected = {{0, 1ULL << 62}};
        BITBOARD and4_got;
        BITBOARD and4_bb_lhs = {{UINT64_MAX >> 8, UINT64_MAX}};
        BITBOARD and4_bb_rhs = {{1ULL << 62, 1ULL << 62}};
        bb_and(&and4_got, &and4_bb_lhs, &and4_bb_rhs);
        ok(bb_eq(&and4_got, &and4_expected),
           "operation works in the higher bits");
}
