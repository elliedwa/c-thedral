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

#ifndef CATHEDRAL_PLACEMENT_GEN_H_
#define CATHEDRAL_PLACEMENT_GEN_H_

#include "bitboard.h"
#include "pieces.h"

typedef struct pl_node_s {
        enum piece_shape shape;
        BITBOARD board;
        struct pl_node_s *next_board;
        struct pl_node_s *next_shape;
} pl_node;

typedef struct {
        pl_node *head;
        pl_node *tail;
} placement_list;

typedef BITBOARD placement_array[2597];

placement_list generate_placements(void);
void generate_placement_array(placement_array pa);

#endif
