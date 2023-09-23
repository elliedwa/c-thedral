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
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>

size_t sq_to_bb_index[100] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

bool
bb_empty(const BITBOARD *board)
{
        return (board->bb[0] == 0) && (board->bb[1] == 0);
}

bool
bb_eq(const BITBOARD *lhs, const BITBOARD *rhs)
{
        return lhs->bb[0] == rhs->bb[0] && lhs->bb[1] == rhs->bb[1];
}

bool
bb_ne(const BITBOARD *lhs, const BITBOARD *rhs)
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
bb_and(BITBOARD *res, const BITBOARD *lhs, const BITBOARD *rhs)
{
        res->bb[0] = lhs->bb[0] & rhs->bb[0];
        res->bb[1] = lhs->bb[1] & rhs->bb[1];
}
void
bb_or(BITBOARD *res, const BITBOARD *lhs, const BITBOARD *rhs)
{
        res->bb[0] = lhs->bb[0] | rhs->bb[0];
        res->bb[1] = lhs->bb[1] | rhs->bb[1];
}

void
bb_xor(BITBOARD *res, const BITBOARD *lhs, const BITBOARD *rhs)
{
        res->bb[0] = lhs->bb[0] ^ rhs->bb[0];
        res->bb[1] = lhs->bb[1] ^ rhs->bb[1];
}

void
bb_copy(BITBOARD *to, const BITBOARD *from)
{
        to->bb[0] = from->bb[0];
        to->bb[1] = from->bb[1];
}

static uint32_t
extract_piece_bit(const BITBOARD *bb)
{
        uint32_t bit          = 0;
        uint32_t light_pieces = bb->bb[0] >> 50;
        uint32_t dark_pieces  = bb->bb[1] >> 50;
        bit |= dark_pieces;
        bit <<= 14;
        bit |= light_pieces;
        return bit;
}

static unsigned int
bb_count_bits(const BITBOARD *bb)
{
        unsigned int nbits = 0;
        for (int i = 0; i < 2; i++) {
                BITBOARD_HALF half = bb->bb[i];
                for (; half; nbits++) {
                        half &= half - 1;
                }
        }
        return nbits;
}

bool
bb_is_placement(const BITBOARD *bb)
{
        uint32_t pb = extract_piece_bit(bb);
        if (bb_empty(bb)) {
                return false;
        }
        if (!pb && bb_count_bits(bb) == 6) {
                return true;
        };
        if ((pb &&
             !(pb & (pb - 1))) /* checks if exactly one piece bit is set */
            && bb_count_bits(bb) < 7 /* checks if no cathedral is present */
        ) {
                return true;
        }
        return false;
}

int
bb_cmp(const void *lhs, const void *rhs)
{
        BITBOARD bb1 = *(const BITBOARD *)lhs;
        BITBOARD bb2 = *(const BITBOARD *)rhs;

        uint32_t pb1 = extract_piece_bit(&bb1);
        uint32_t pb2 = extract_piece_bit(&bb2);

        if (bb_ne(&bb1, &bb2)) {

                if (pb1 < pb2) {
                        return -1;
                }
                if (pb1 > pb2) {
                        return 1;
                }

                if (bb1.bb[1] < bb2.bb[1]) {
                        return -1;
                }
                if (bb1.bb[1] > bb2.bb[1]) {
                        return 1;
                }
                if (bb1.bb[0] < bb2.bb[0]) {
                        return -1;
                }
                if (bb1.bb[0] > bb2.bb[0]) {
                        return 1;
                }
        }
        return 0;
}

void
DEBUG_print_bitboard_visual(BITBOARD *b)
{
        BITBOARD_HALF hfs[2] = {b->bb[0], b->bb[1]};
        for (size_t sq = 0; sq < 100; sq++) {
                BITBOARD_HALF *hf = &hfs[sq_to_bb_index[sq]];
                putchar('0' + (char)(*hf & 1));
                if (sq % 10 == 9) {
                        putchar('\n');
                }
                *hf >>= 1;
        }
        putchar('\n');
}

void
DEBUG_print_bitboard_hex(BITBOARD *b)
{
        printf("%.16" PRIx64 "|%.16" PRIx64 "\n", b->bb[0], b->bb[1]);
}
