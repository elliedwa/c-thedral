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

#include "cthedral/placement_gen.h"
#include "cthedral/bitboard.h"
#include "cthedral/pbb.h"
#include "cthedral/pieces.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct piece_data {
        enum piece_shape id;
        int symmetry;
        PADDED_BITBOARD_HALF masks[4];
        int how_many;
        enum piece pieces[4];
};

/*static BITBOARD get_placement(enum piece_shape shape, int sym, int shift);*/

static const struct piece_data PIECE_DATA_ARRAY[NUM_PIECE_SHAPES] = {
    [SHAPE_CATHEDRAL] = {SHAPE_CATHEDRAL, 1, {0x400803802}, 1, {CATHEDRAL}},
    [SHAPE_TAVERN]    = {SHAPE_TAVERN,
                         1,
                         {0x1},
                         4,
                         {LIGHT_TAVERN_1, LIGHT_TAVERN_2, DARK_TAVERN_1,
                          DARK_TAVERN_2}},
    [SHAPE_STABLE]    = {SHAPE_STABLE,
                         2,
                         {0x801, 0x3},
                         4,
                         {LIGHT_STABLE_1, LIGHT_STABLE_2, DARK_STABLE_1,
                          DARK_STABLE_2}},
    [SHAPE_INN]       = {SHAPE_INN,
                         4,
                         {0x1801, 0x803, 0x1003, 0x1802},
                         4,
                         {LIGHT_INN_1, LIGHT_INN_2, DARK_INN_1, DARK_INN_2}},

    [SHAPE_BRIDGE] =
        {SHAPE_BRIDGE, 2, {0x400801, 0x7}, 2, {LIGHT_BRIDGE, DARK_BRIDGE}},
    [SHAPE_SQUARE] =
        {SHAPE_SQUARE, 1, {0x1803}, 2, {LIGHT_SQUARE, DARK_SQUARE}},
    [SHAPE_ABBEY_LIGHT] =
        {SHAPE_ABBEY_LIGHT, 2, {0x801801, 0x1806}, 1, {LIGHT_ABBEY}},
    [SHAPE_ABBEY_DARK] =
        {SHAPE_ABBEY_DARK, 2, {0x401802, 0x3003}, 1, {DARK_ABBEY}},
    [SHAPE_MANOR] = {SHAPE_MANOR,
                     4,
                     {0x3802, 0x401801, 0x1007, 0x801802},
                     2,
                     {LIGHT_MANOR, DARK_MANOR}},
    [SHAPE_TOWER] = {SHAPE_TOWER,
                     4,
                     {0xc03004, 0x1801801, 0x401806, 0x1003003},
                     2,
                     {LIGHT_TOWER, DARK_TOWER}},
    [SHAPE_INFIRMARY] =
        {SHAPE_INFIRMARY, 1, {0x803802}, 2, {LIGHT_INFIRMARY, DARK_INFIRMARY}},
    [SHAPE_CASTLE]        = {SHAPE_CASTLE,
                             4,
                             {0xc01003, 0x3805, 0xc00803, 0x2807},
                             2,
                             {LIGHT_CASTLE, DARK_CASTLE}},
    [SHAPE_ACADEMY_LIGHT] = {SHAPE_ACADEMY_LIGHT,
                             4,
                             {0x1801802, 0x403802, 0x803003, 0x803804},
                             1,
                             {LIGHT_ACADEMY}},
    [SHAPE_ACADEMY_DARK]  = {SHAPE_ACADEMY_DARK,
                             4,
                             {0xc03002, 0x803801, 0x801806, 0x1003802},
                             1,
                             {DARK_ACADEMY}},
};

/*
BITBOARD
get_placement(enum piece_shape shape, int sym, int shift)
{
        struct piece_data piece = PIECE_DATA_ARRAY[shape];
        assert(sym >= 0 && sym < 4);
        PADDED_BITBOARD board = {{piece.masks[sym % (piece.symmetry + 1)]}};
        while (shift--) {
                pbb_shl(board);
        }
        return board;
}
*/

/*
 *static const int placements_per_shape[NUM_PIECE_SHAPES] = {
 *    [SHAPE_CATHEDRAL] = 56,      [SHAPE_TAVERN] = 100 * 4,
 *    [SHAPE_STABLE] = 180 * 4,    [SHAPE_INN] = 324 * 4,
 *    [SHAPE_BRIDGE] = 160 * 2,    [SHAPE_SQUARE] = 81 * 2,
 *    [SHAPE_ABBEY_DARK] = 144,    [SHAPE_ABBEY_LIGHT] = 144,
 *    [SHAPE_MANOR] = 288 * 2,     [SHAPE_INFIRMARY] = 64 * 2,
 *    [SHAPE_TOWER] = 256 * 2,     [SHAPE_CASTLE] = 288 * 2,
 *    [SHAPE_ACADEMY_LIGHT] = 256, [SHAPE_ACADEMY_DARK] = 256,
 *};
 */

int
generate_placement_array(placement_array *pa)
{
        int ndx = 0;
        for (int shape = 0; shape < NUM_PIECE_SHAPES; shape++) {
                struct piece_data data = PIECE_DATA_ARRAY[shape];

                for (int mask_index = 0; mask_index < data.symmetry;
                     mask_index++) {
                        PADDED_BITBOARD padded_mask = {
                            {data.masks[mask_index], 0}};
                        while (!pbb_check_stop_bit(padded_mask)) {
                                if (pbb_validate(padded_mask)) {
                                        for (int pce = 0; pce < data.how_many;
                                             pce++) {
                                                BITBOARD bit =
                                                    piece_bit(data.pieces[pce]);
                                                BITBOARD mask =
                                                    pbb_remove_padding(
                                                        padded_mask);
                                                BITBOARD plcmt = {{0, 0}};
                                                bb_or(&plcmt, &mask, &bit);
                                                bb_copy(&pa->bb[ndx++], &plcmt);
                                        }
                                }
                                pbb_shl(&padded_mask);
                        }
                }
        }
        qsort(pa->bb, 5546, sizeof(BITBOARD), bb_cmp);
        return ndx;
}

placement_array *
pa_alloc(void)
{
        return (placement_array *)malloc(sizeof(placement_array));
}
