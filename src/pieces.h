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

#ifndef CATHEDRAL_PIECES_H_
#define CATHEDRAL_PIECES_H_

enum piece {
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
        NUM_PIECES_PER_SIDE,
        DARK_TAVERN_1 = 0x10,
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

#define WHICH_PIECE(x) ((x) & (0x10 - 1))
#define WHOSE_PIECE(x) ((x) >> 4)

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

static const enum piece PIECES_BY_SHAPE[NUM_PIECE_SHAPES][4] = {
    [SHAPE_TAVERN]        = {LIGHT_TAVERN_1, LIGHT_TAVERN_2, DARK_TAVERN_1,
                             DARK_TAVERN_2},
    [SHAPE_STABLE]        = {LIGHT_STABLE_1, LIGHT_STABLE_2, DARK_STABLE_1,
                             DARK_STABLE_2},
    [SHAPE_INN]           = {LIGHT_INN_1, LIGHT_INN_2, DARK_INN_1, DARK_INN_2},
    [SHAPE_BRIDGE]        = {LIGHT_BRIDGE, DARK_BRIDGE},
    [SHAPE_SQUARE]        = {LIGHT_SQUARE, DARK_SQUARE},
    [SHAPE_ABBEY_LIGHT]   = {LIGHT_ABBEY},
    [SHAPE_ABBEY_DARK]    = {DARK_ABBEY},
    [SHAPE_MANOR]         = {LIGHT_MANOR, DARK_MANOR},
    [SHAPE_TOWER]         = {LIGHT_TOWER, DARK_TOWER},
    [SHAPE_CASTLE]        = {LIGHT_CASTLE, DARK_CASTLE},
    [SHAPE_INFIRMARY]     = {LIGHT_INFIRMARY, DARK_INFIRMARY},
    [SHAPE_ACADEMY_LIGHT] = {LIGHT_ACADEMY},
    [SHAPE_ACADEMY_DARK]  = {DARK_ACADEMY},
};

#endif
