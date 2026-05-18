#include "gear_ratios.h"
#include "munit.h"

static MunitResult test_part_1(const MunitParameter[], void *) {
  munit_assert_int(part_1("../data/example_input_part_1.txt"), ==, 4361);
  return MUNIT_OK;
}

static MunitResult test_part_2(const MunitParameter[], void *) {
  munit_assert_int(part_2("../data/example_input_part_2.txt"), ==, 467835);
  return MUNIT_OK;
}

static MunitTest tests[] = {
    {"/part_1", test_part_1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/part_2", test_part_2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static const MunitSuite suite = {"/gear_ratios", tests, NULL, 1,
                                 MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}