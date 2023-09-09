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

#include "cthedral/bitboard.h"
#include "tap.h"
#include <stdint.h>

int
main(void)
{
        plan(NO_PLAN);

        BITBOARD empty = {{0, 0}};
        ok(bb_empty(&empty), "empty bitboards can be detected");
        BITBOARD not_empty = {{0, 1}};
        ok(!bb_empty(&not_empty), "non-empty bitboards can also be detected");

        ok(bb_eq(&empty, &empty), "a bitboard equals itself");
        ok(bb_ne(&empty, &not_empty),
           "a bitboard does not equal some other bitboard");
        cmp_ok(bb_eq(&empty, &empty), "==", !bb_ne(&empty, &empty),
               "bb_eq and bb_ne are inverses of each other");

        BITBOARD and1_expected = {{0, 0}};
        BITBOARD and1_got;
        BITBOARD and1_bb_lhs = {{0, 1}};
        BITBOARD and1_bb_rhs = {{1, 0}};
        bb_and(&and1_got, &and1_bb_lhs, &and1_bb_rhs);
        cmp_mem(&and1_got, &and1_expected, sizeof(BITBOARD),
                "bb_and: boards with no overlap return empty board");

        BITBOARD and2_expected = {{0, 1}};
        BITBOARD and2_got;
        BITBOARD and2_bb_lhs = {{0, 1}};
        BITBOARD and2_bb_rhs = {{1, 1}};
        bb_and(&and2_got, &and2_bb_lhs, &and2_bb_rhs);
        cmp_mem(&and2_got, &and2_expected, sizeof(BITBOARD),
                "bb_and: boards with some overlap return all common bits");

        BITBOARD and3_expected = {{0, 0x3c0c3}};
        BITBOARD and3_got;
        BITBOARD and3_bb_lhs = {{0, 0x3c0c3}};
        BITBOARD and3_bb_rhs = {{0, 0x3c0c3}};
        bb_and(&and3_got, &and3_bb_lhs, &and3_bb_rhs);
        cmp_mem(&and3_got, &and3_expected, sizeof(BITBOARD),
                "bb_and: board & itself returns itself");

        BITBOARD and4_expected = {{0, 1ULL << 62}};
        BITBOARD and4_got;
        BITBOARD and4_bb_lhs = {{UINT64_MAX >> 8, UINT64_MAX}};
        BITBOARD and4_bb_rhs = {{1ULL << 62, 1ULL << 62}};
        bb_and(&and4_got, &and4_bb_lhs, &and4_bb_rhs);
        cmp_mem(&and4_got, &and4_expected, sizeof(BITBOARD),
                "bb_and: operation works in the higher bits");

        BITBOARD or1_expected = {{1, 1}};
        BITBOARD or1_got;
        BITBOARD or1_bb_lhs = {{0, 1}};
        BITBOARD or1_bb_rhs = {{1, 0}};
        bb_or(&or1_got, &or1_bb_lhs, &or1_bb_rhs);
        cmp_mem(&or1_got, &or1_expected, sizeof(BITBOARD),
                "bb_or: boards with no overlap return all bits set in either "
                "board");

        BITBOARD or2_expected = {{1, 1}};
        BITBOARD or2_got;
        BITBOARD or2_bb_lhs = {{0, 1}};
        BITBOARD or2_bb_rhs = {{1, 1}};
        bb_or(&or2_got, &or2_bb_lhs, &or2_bb_rhs);
        cmp_mem(&or2_got, &or2_expected, sizeof(BITBOARD),
                "bb_or: boards with some overlap return all bits set in either "
                "board");

        BITBOARD or3_expected = {{0xffffffffffffULL, 0xffffffffffffULL << 16}};
        BITBOARD or3_got;
        BITBOARD or3_bb_lhs = {{0xff0ff0ff0ff0ULL, 0xff0ff0ff0ff0ULL << 16}};
        BITBOARD or3_bb_rhs = {{0x0ff0ff0ff0ffULL, 0xf0ff0ff0ff0fULL << 16}};
        bb_or(&or3_got, &or3_bb_lhs, &or3_bb_rhs);
        cmp_mem(&or3_got, &or3_expected, sizeof(BITBOARD),
                "bb_or: operation works in more complex states");

        BITBOARD or4_expected = {
            {(UINT64_MAX >> 8) | (1ULL << 62), UINT64_MAX}};
        BITBOARD or4_got;
        BITBOARD or4_bb_lhs = {{UINT64_MAX >> 8, UINT64_MAX}};
        BITBOARD or4_bb_rhs = {{1ULL << 62, 1ULL << 62}};
        bb_or(&or4_got, &or4_bb_lhs, &or4_bb_rhs);
        cmp_mem(&or4_got, &or4_expected, sizeof(BITBOARD),
                "bb_or: operation works in the higher bits");


        done_testing();
}
