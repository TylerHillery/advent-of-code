#include "munit.h"
#include "trebuchet.h"
#include <limits.h>

static MunitResult test_get_first_and_last_digit_part_1(const MunitParameter[],
                                                        void *) {
  munit_assert_int(get_first_and_last_digit_part_1("1abc2"), ==, 12);
  munit_assert_int(get_first_and_last_digit_part_1("treb7uchet"), ==, 77);
  return MUNIT_OK;
}

static MunitResult test_get_first_and_last_digit_part_2(const MunitParameter[],
                                                        void *) {
  munit_assert_int(get_first_and_last_digit_part_2("two1nine"), ==, 29);
  munit_assert_int(get_first_and_last_digit_part_2("1abc2"), ==, 12);
  return MUNIT_OK;
}

static MunitResult test_find_char(const MunitParameter[], void *) {
  munit_assert_int(find_char("1abc2\n", '\n', 0), ==, 5);
  munit_assert_size(find_char("1abc2", '\n', 0), ==, SIZE_MAX);
  return MUNIT_OK;
}

static MunitResult test_part_1(const MunitParameter[], void *) {
  char input[] = "1abc2\npqr3stu8vwx\na1b2c3d4e5f\ntreb7uchet\n";
  munit_assert_int(part_1(input), ==, 142);
  return MUNIT_OK;
}

static MunitResult test_part_2(const MunitParameter[], void *) {
  char input[] = "two1nine\neightwothree\nabcone2threexyz\nxtwone3four\n4nineei"
                 "ghtseven2\nzoneight234\n7pqrstsixteen\n";
  munit_assert_int(part_2(input), ==, 281);
  return MUNIT_OK;
}

static MunitTest tests[] = {
    {"/get_first_and_last_digit_part_1", test_get_first_and_last_digit_part_1,
     NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/get_first_and_last_digit_part_2", test_get_first_and_last_digit_part_2,
     NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/find_char", test_find_char, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/part_1", test_part_1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/part_2", test_part_2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static const MunitSuite suite = {"/trebuchet", tests, NULL, 1,
                                 MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
