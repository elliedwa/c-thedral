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

int
main(void)
{
        plan(NO_PLAN);
        placement_array pa;
        lives_ok(generate_placement_array(&pa);
                 , "generate_placement_array() does not segfault");
        BITBOARD first_cathedral_plcmt = {{0x400803802, 0}};
        cmp_mem(&pa.bb[0], &first_cathedral_plcmt, sizeof(BITBOARD));
        for (size_t i = 0; i < (sizeof(placement_array) / sizeof(BITBOARD));
             i++) {
                DEBUG_print_bitboard_hex(pa.bb[i]);
        }
        done_testing();
}
