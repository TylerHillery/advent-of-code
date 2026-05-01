#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file(char *path);
char *read_line(char *file, int offset);

int is_cube_under_max(char *color, int num_of_cubes) {
  const int MAX_RED_CUBES = 12;
  const int MAX_GREEN_CUBES = 13;
  const int MAX_BLUE_CUBES = 14;

  if (strcmp(color, "red") == 0) {
    return num_of_cubes <= MAX_RED_CUBES;
  } else if (strcmp(color, "blue") == 0) {
    return num_of_cubes <= MAX_BLUE_CUBES;
  } else if (strcmp(color, "green") == 0) {
    return num_of_cubes <= MAX_GREEN_CUBES;
  }

  // blow up this shouldn't happen
  fprintf(stderr, "Got unknown color %s\n", color);
  exit(1);
}

int is_game_valid_part_1(char *game) {

  // this assumes game id is < 1000 we can only store 999 need room for \0
  char game_id[4];

  // get game id
  int i;
  for (i = 5; game[i] != ':'; i++) {
    game_id[i - 5] = game[i];
  }

  game_id[i - 5] = '\0';

  // assumes we wont cube number greater than 999
  char num_of_cubes_buffer[4];
  int num_of_cubes = -1;
  // green is longest color string, which 5 + 1 for null termination
  char cube_color_buffer[6];
  // the i should have ended at the :, so we added two one account for space
  // after
  int offset = i + 2;

  for (i = offset;; i++) {
    if (strncmp(&game[i], ", ", 2) == 0 || (strncmp(&game[i], "; ", 2) == 0) ||
        game[i] == '\0') {
      // we know the offset + i should give us the color
      strncpy(cube_color_buffer, &game[offset], i - offset);
      cube_color_buffer[i - offset] = '\0';

      // if we find a cube over max we can return right away
      if (!is_cube_under_max(cube_color_buffer, num_of_cubes)) {
        return 0;
      }

      // last color in the last set
      if (game[i] == '\0') {
        break;
      }

      i += 2;
      offset = i;

    } else if (game[i] == ' ') {
      // we know than the offset + i should give us the string number of cubes
      // we really should check if the size is longer than buffer but ignoring
      // for now
      strncpy(num_of_cubes_buffer, &game[offset], i - offset);
      num_of_cubes_buffer[i - offset] = '\0';
      // should use strtol for better error handeling
      num_of_cubes = atoi(num_of_cubes_buffer);
      offset = i + 1;
    }
  }

  // should use strtol
  return atoi(game_id);
}

int part_1(char *buffer) {

  int file_length = strlen(buffer);
  int current_length = 0;
  int acc = 0;

  do {
    char *line_buffer = read_line(buffer, current_length);
    int line_length = strlen(line_buffer);
    current_length += line_length + 1;
    int game_id = is_game_valid_part_1(line_buffer);
    free(line_buffer);
    acc += game_id;
  } while (current_length < file_length);

  return acc;
}

char *read_file(char *path) {

  FILE *file = fopen(path, "rb");

  if (file == NULL) {
    printf("error opening file %s", path);
    return NULL;
  }

  if (fseek(file, 0, SEEK_END) != 0) {
    fclose(file);
    return NULL;
  };

  long size = ftell(file);

  if (size < 0) {
    fclose(file);
    return NULL;
  }

  rewind(file);

  char *buffer = malloc(size + 1);

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

char *read_line(char *file, int offset) {
  int i;
  for (i = offset; file[i] != '\n' && file[i] != '\0'; i++)
    ;

  char *buffer = malloc(i - offset + 1);
  strncpy(buffer, &file[offset], i - offset);
  buffer[i] = '\0';
  return buffer;
}