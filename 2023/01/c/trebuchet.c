#include "trebuchet.h"
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long get_first_and_last_digit_part_1(char *str) {
  char first = '\0';
  char last = '\0';

  for (size_t i = 0; str[i] != '\0'; i++) {
    if (isdigit((unsigned char)str[i])) {
      if (first == '\0') {
        first = str[i];
      }
      last = str[i];
    }
  }
  char first_and_last[3] = {first, last, '\0'};
  return strtol(first_and_last, NULL, 10);
}

long get_first_and_last_digit_part_2(char *str) {
  const char str_numbers[9][6] = {"one", "two",   "three", "four", "five",
                                  "six", "seven", "eight", "nine"};
  char first = '\0';
  char last = '\0';

  for (size_t i = 0; str[i] != '\0'; i++) {
    if (isdigit((unsigned char)str[i])) {
      if (first == '\0') {
        first = str[i];
      }
      last = str[i];
      continue;
    }

    for (int j = 0; j < 9; j++) {
      const char *str_num = str_numbers[j];
      size_t len = strlen(str_num);
      if (strncmp(&str[i], str_num, len) == 0) {
        char c = (j + 1 + '0');
        if (first == '\0') {
          first = c;
        }
        last = c;
        break;
      }
    }
  }
  char first_and_last[3] = {first, last, '\0'};
  return strtol(first_and_last, NULL, 10);
}

size_t find_char(char *str, char c, size_t offset) {
  for (size_t i = offset; str[i] != '\0'; i++) {
    if (str[i] == c) {
      return i;
    }
  }
  return SIZE_MAX;
}

int main_loop(char *input, long (*cb)(char *)) {
  size_t i;
  size_t offset = 0;
  int sum = 0;
  size_t buffer_size = 128;
  char *buffer = malloc(buffer_size);

  if (buffer == NULL) {
    return -1;
  }

  while ((i = find_char(input, '\n', offset)) != SIZE_MAX) {
    // i is now the index of the "next" \n
    // input[offset] to input[i] gives us the full line excluding the \n
    size_t line_length = i - offset;

    // check to ensure line length is not greater than current buffer size
    // plus one because we need to account for null terminator.
    if (line_length + 1 > buffer_size) {
      buffer_size = line_length + 1;
      char *tmp = realloc(buffer, buffer_size);
      if (tmp == NULL) {
        free(buffer);
        return -1;
      }
      buffer = tmp;
    }

    memcpy(buffer, &input[offset], line_length);
    buffer[line_length] = '\0';
    // printf("DEBUG[print line]: %s\n", buffer);
    sum += cb(buffer);
    offset = i + 1;
  }

  if (input[offset] != '\0') {
    size_t line_length = strlen(&input[offset]);

    if (line_length + 1 > buffer_size) {
      buffer_size = line_length + 1;
      char *tmp = realloc(buffer, buffer_size);
      if (tmp == NULL) {
        free(buffer);
        return -1;
      }
      buffer = tmp;
    }

    memcpy(buffer, &input[offset], line_length);
    buffer[line_length] = '\0';
    // printf("DEBUG[print final line]: %s\n", buffer);
    sum += cb(buffer);
  }
  free(buffer);
  return sum;
}

int part_1(char *input) {
  return main_loop(input, &get_first_and_last_digit_part_1);
}

int part_2(char *input) {
  return main_loop(input, &get_first_and_last_digit_part_2);
}

char *read_file(const char *path) {
  FILE *file = fopen(path, "rb");
  if (file == NULL)
    return NULL;

  if (fseek(file, 0, SEEK_END) != 0) {
    fclose(file);
    return NULL;
  }

  long size = ftell(file);
  if (size < 0) {
    fclose(file);
    return NULL;
  }

  rewind(file);

  char *buffer = malloc((size_t)size + 1);
  if (buffer == NULL) {
    fclose(file);
    return NULL;
  }

  size_t bytes_read = fread(buffer, 1, (size_t)size, file);
  if (bytes_read != (size_t)size) {
    free(buffer);
    fclose(file);
    return NULL;
  }

  buffer[bytes_read] = '\0';
  fclose(file);
  return buffer;
}
