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

#include "cthedral/placement_gen.h"
#include <string.h>

int
main(void)
{
        placement_array pa;
        generate_placement_array(pa);
        BITBOARD expected = {{1, 0}};
        if (memcmp(&pa[0], &expected, sizeof(BITBOARD))) {
                return 0;
        }
        return 1;
}
