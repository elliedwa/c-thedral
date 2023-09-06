#include "cthedral/bitboard.h"
#include "cthedral/placement_gen.h"
#include "rexo.h"

RX_TEST_CASE(test_runner_works, rexo_works)
{
        RX_INT_REQUIRE_EQUAL(2 * 3 * 7, 42);
}

RX_SET_UP(placement_array_set_up)
{
        placement_array *pl;

        pl = (placement_array *)RX_DATA;
        generate_placement_array(*pl);
        return RX_SUCCESS;
}

RX_FIXTURE(placement_array_fixture, placement_array,
           .set_up = placement_array_set_up);

RX_TEST_CASE(placement_array, placement_array_size)
{
        placement_array *pl;
        pl = (placement_array *)RX_DATA;
        RX_INT_CHECK_EQUAL(2597 * sizeof(BITBOARD), sizeof(*pl));
}

int
main(int argc, const char **argv)
{
        return rx_main(0, NULL, argc, argv) == RX_SUCCESS ? 0 : 1;
}
