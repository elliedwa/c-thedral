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

#ifndef CATHEDRAL_PLACEMENT_GEN_H_
#define CATHEDRAL_PLACEMENT_GEN_H_

#include "bitboard.h"
#include "pieces.h"
#include <stdlib.h>

#define PA_CAPACITY 8192

typedef struct placement_array {
        BITBOARD bb[PA_CAPACITY];
} placement_array;

placement_array *pa_alloc(void);

int generate_placement_array(placement_array *pa);

#endif
