#include "cube_conundrum.h"
#include "munit.h"

static MunitResult test_part_1(const MunitParameter[], void *) {
  char input[] =
      "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green\n"
      "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue\n"
      "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 "
      "red\n"
      "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 "
      "red\n"
      "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green";
  munit_assert_int(part_1(input), ==, 8);
  return MUNIT_OK;
}

static MunitResult test_part_2(const MunitParameter[], void *) {
  char input[] =
      "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green\n"
      "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue\n"
      "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 "
      "red\n"
      "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 "
      "red\n"
      "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green\n";
  munit_assert_int(part_2(input), ==, 2286);
  return MUNIT_OK;
}

static MunitTest tests[] = {
    {"/part_1", test_part_1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/part_2", test_part_2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static const MunitSuite suite = {"/cube_conundrum", tests, NULL, 1,
                                 MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}