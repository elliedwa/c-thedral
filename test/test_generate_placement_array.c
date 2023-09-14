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
#include "cthedral/placement_gen.h"
#include "tap.h"

#include <stdlib.h>

int
main(void)
{
        plan(2);
        placement_array *pa = pa_alloc();
        ok(pa != NULL, "placement_array can be allocated");
        int num_placements = 0;
        num_placements     = generate_placement_array(pa);
        cmp_ok(num_placements, "==", 5546,
               "generates expected number of placements");
        free(pa);
        done_testing();
}
