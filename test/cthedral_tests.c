#include <tau/tau.h>
#include <cthedral/placement_gen.h>


TAU_MAIN()

TEST(TestRunner, TauWorks) {
	CHECK(1);
}

TEST(PlacementArray, TypeSize) {
	placement_array pa;
	CHECK(sizeof(pa)/sizeof(*pa) == 2597, "Expected placement_array to have 2597 BITBOARDs");
}
