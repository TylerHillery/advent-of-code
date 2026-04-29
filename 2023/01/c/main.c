#include "trebuchet.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char *path = "../data/input.txt";

  char *buffer = read_file(path);
  if (buffer == NULL) {
    fprintf(stderr, "Error reading file %s\n", path);
    return 1;
  }

  printf("Part 1: %d\n", part_1(buffer));
  printf("Part 2: %d\n", part_2(buffer));
  free(buffer);
  return 0;
}
