#ifndef TREBUCHET_H
#define TREBUCHET_H

#include <stddef.h>

char *read_file(const char *path);
long get_first_and_last_digit_part_1(char *str);
long get_first_and_last_digit_part_2(char *str);
size_t find_char(char *str, char c, size_t offset);
int part_1(char *input);
int part_2(char *input);

#endif