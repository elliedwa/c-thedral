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

#ifndef CATHEDRAL_PIECES_H_
#define CATHEDRAL_PIECES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cthedral/bitboard.h"

#define NUM_PIECES 29

enum piece {
        CATHEDRAL,
        LIGHT_TAVERN_1,
        LIGHT_TAVERN_2,
        LIGHT_STABLE_1,
        LIGHT_STABLE_2,
        LIGHT_INN_1,
        LIGHT_INN_2,
        LIGHT_BRIDGE,
        LIGHT_SQUARE,
        LIGHT_ABBEY,
        LIGHT_MANOR,
        LIGHT_TOWER,
        LIGHT_CASTLE,
        LIGHT_INFIRMARY,
        LIGHT_ACADEMY,
        DARK_PIECE_OFFSET = 0x10,
        DARK_TAVERN_1     = LIGHT_TAVERN_1 + DARK_PIECE_OFFSET,
        DARK_TAVERN_2,
        DARK_STABLE_1,
        DARK_STABLE_2,
        DARK_INN_1,
        DARK_INN_2,
        DARK_BRIDGE,
        DARK_SQUARE,
        DARK_ABBEY,
        DARK_MANOR,
        DARK_TOWER,
        DARK_CASTLE,
        DARK_INFIRMARY,
        DARK_ACADEMY,
};

#define NUM_PIECES_PER_SIDE LIGHT_ACADEMY

extern size_t WHOSE_PIECE[DARK_ACADEMY + 1];

enum piece_shape {
        SHAPE_TAVERN,
        SHAPE_STABLE,
        SHAPE_INN,
        SHAPE_BRIDGE,
        SHAPE_SQUARE,
        SHAPE_ABBEY_LIGHT,
        SHAPE_ABBEY_DARK,
        SHAPE_MANOR,
        SHAPE_TOWER,
        SHAPE_CASTLE,
        SHAPE_INFIRMARY,
        SHAPE_ACADEMY_LIGHT,
        SHAPE_ACADEMY_DARK,
        SHAPE_CATHEDRAL,
        NUM_PIECE_SHAPES
};

BITBOARD piece_bit(enum piece p);

#ifdef __cplusplus
}
#endif

#endif
