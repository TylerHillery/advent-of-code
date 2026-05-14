#include <stdio.h>
#include <stdlib.h>

struct matrix {
  int rows;
  int cols;
  int **data;
};

struct gear_ratio {
  int row;
  int col;
  int length;
  int ratio;
};

void matrix_free_rows(struct matrix *matrix) {
  for (int i = 0; i < matrix->rows; i++) {
    free(matrix->data[i]);
  }
}

void matrix_append_row(struct matrix *matrix) {
  int **temp = NULL;
  int *row = calloc(matrix->cols, sizeof(int));
  if (row == NULL) {
    perror("row allocation failure");
    exit(EXIT_FAILURE);
  }

  temp = realloc(matrix->data, sizeof(int *) * (matrix->rows + 1));
  if (temp == NULL) {
    matrix_free_rows(matrix);
    free(matrix->data);
    free(row);
    perror("matrix ralloc");
    exit(EXIT_FAILURE);
  }

  matrix->data = temp;
  matrix->data[matrix->rows++] = row;
}

void matrix_print(struct matrix *matrix) {
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->cols; j++) {
      printf("%d", matrix->data[i][j]);
    }
    printf("\n");
  }
}

int part_1_is_a_symbol(char c) {
  // not . and can't be converted to an int
  int i = c - '0';
  return (i < 0 || i > 10) && c != '.';
}

int part_2_is_a_symbol(char c) { return c == '*'; }

int part_1_is_valid_gear_ratio(struct gear_ratio *gr, struct matrix *matrix) {
  // make this min row equal to the max(row -1, 0)
  // make the max row equal to th emin (row+1, matrix->rows)
  int min_row = (gr->row - 1) > 0 ? gr->row - 1 : 0;
  int max_row = (gr->row + 2) < matrix->rows ? gr->row + 2 : matrix->rows;

  // make this min row equal to the max(col- 1, 0)
  // make the max row equal to th min(col+1, matrix->cols)
  int min_col = (gr->col - 1) > 0 ? gr->col - 1 : 0;
  int max_col = (gr->col + gr->length + 1) < matrix->cols
                    ? gr->col + gr->length + 1
                    : matrix->cols;

  for (int row = min_row; row < max_row; row++) {
    for (int col = min_col; col < max_col; col++) {
      // skip the actual position of the gear ratio in the matrix
      if (row == gr->row && col == gr->col) {
        col += gr->length - 1;
        continue;
      }

      if (matrix->data[row][col]) {
        return gr->ratio;
      }
    }
  }
  return 0;
}

int part_1(char *path) {
  char *line = NULL;
  struct matrix matrix = {.rows = 0, .cols = 0, .data = NULL};
  struct gear_ratio *gear_ratios = NULL;
  int count = 0;
  int capacity = 0;

  size_t size = 0;
  ssize_t nread;
  FILE *f = fopen(path, "r");

  if (!f) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  struct node *prev_node = NULL;

  while ((nread = getline(&line, &size, f)) != -1) {

    // we know this is the first line in loop when cols = 0;
    if (matrix.cols == 0) {
      matrix.cols = nread - 1;
    }
    matrix_append_row(&matrix);

    int ratio = 0;
    int length = 0;

    // loop through each char in the row, (AKA are columns in the matrix)
    for (int i = 0; i < matrix.cols; i++) {
      int num = line[i] - '0';
      if (num >= 0 && num <= 10) {
        // "trick" to add append digits e.g. reading 412 char by char
        // (0 * 10)  + 4 = 4
        // (4 * 10)  + 1 = 41
        // (41 * 10) + 1 = 412
        ratio = (ratio * 10) + num;
        length++;
        continue;
      }

      // keep a sparate matrix of which cordinates have a "symbol", this will
      // make it easy to check in O(1) time if specific (x,y) aka (col, row)
      // has a valid symbol
      if (part_1_is_a_symbol(line[i])) {
        matrix.data[matrix.rows - 1][i] = 1;
      }

      // this means we hit a symbol or a period so lets take a current state
      // and create neccessary data structures before resetting onto next
      // we only need to do this when ratio > 0 which means we "found" a gear
      // ration
      if (ratio > 0) {
        if (count == capacity) {
          capacity = capacity == 0 ? 8 : capacity * 2;
          gear_ratios =
              realloc(gear_ratios, sizeof(struct gear_ratio) * capacity);
        }
        gear_ratios[count++] = (struct gear_ratio){.col = i - length,
                                                   .row = matrix.rows - 1,
                                                   .length = length,
                                                   .ratio = ratio};
        ratio = 0;
        length = 0;
      }
    }
    // if ratio ends at end of line we have to do this check again before next
    // row.
    if (ratio > 0) {
      if (count == capacity) {
        capacity = capacity == 0 ? 8 : capacity * 2;
        gear_ratios =
            realloc(gear_ratios, sizeof(struct gear_ratio) * capacity);
      }
      gear_ratios[count++] = (struct gear_ratio){.col = matrix.cols - length,
                                                 .row = matrix.rows - 1,
                                                 .length = length,
                                                 .ratio = ratio};
      ratio = 0;
      length = 0;
    }
  }
  // printf("Total rows %d\n", matrix.rows);
  // printf("Total cols %d\n", matrix.cols);
  // matrix_print(&matrix);
  int result = 0;
  for (int i = 0; i < count; i++) {
    struct gear_ratio gear_ratio = gear_ratios[i];
    // printf("gear ratio: %d at row: %d col: %d", gear_ratio.ratio,
    //  gear_ratio.row, gear_ratio.col);
    int ratio = part_1_is_valid_gear_ratio(&gear_ratio, &matrix);
    // ratio ? printf(" is valid") : printf(" not valid");
    // printf("\n");
    result += ratio;
  }
  free(gear_ratios);
  matrix_free_rows(&matrix);
  free(matrix.data);
  return result;
}

int part_is_2_overlap_between_two_segements(int min_x1, int min_x2, int max_x1,
                                            int max_x2) {
  int max_of_mins = min_x1 >= min_x2 ? min_x1 : min_x2;
  int min_of_maxs = max_x1 <= max_x2 ? max_x1 : max_x2;
  return max_of_mins <= min_of_maxs;
}

int part_2(char *path) {
  char *line = NULL;
  struct matrix matrix = {.rows = 0, .cols = 0, .data = NULL};
  struct gear_ratio *gear_ratios = NULL;
  int count = 0;
  int capacity = 0;

  size_t size = 0;
  ssize_t nread;
  FILE *f = fopen(path, "r");

  if (!f) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  struct node *prev_node = NULL;

  while ((nread = getline(&line, &size, f)) != -1) {

    // we know this is the first line in loop when cols = 0;
    if (matrix.cols == 0) {
      matrix.cols = nread - 1;
    }
    matrix_append_row(&matrix);

    int ratio = 0;
    int length = 0;

    // loop through each char in the row, (AKA are columns in the matrix)
    for (int i = 0; i < matrix.cols; i++) {
      int num = line[i] - '0';
      if (num >= 0 && num <= 10) {
        // "trick" to add append digits e.g. reading 412 char by char
        // (0 * 10)  + 4 = 4
        // (4 * 10)  + 1 = 41
        // (41 * 10) + 1 = 412
        ratio = (ratio * 10) + num;
        length++;
        continue;
      }

      // keep a sparate matrix of which cordinates have a "symbol", this will
      // make it easy to check in O(1) time if specific (x,y) aka (col, row)
      // has a valid symbol
      if (part_2_is_a_symbol(line[i])) {
        matrix.data[matrix.rows - 1][i] = 1;
      }

      // this means we hit a symbol or a period so lets take a current state
      // and create neccessary data structures before resetting onto next
      // we only need to do this when ratio > 0 which means we "found" a gear
      // ration
      if (ratio > 0) {
        if (count == capacity) {
          capacity = capacity == 0 ? 8 : capacity * 2;
          gear_ratios =
              realloc(gear_ratios, sizeof(struct gear_ratio) * capacity);
        }
        gear_ratios[count++] = (struct gear_ratio){.col = i - length,
                                                   .row = matrix.rows - 1,
                                                   .length = length,
                                                   .ratio = ratio};
        ratio = 0;
        length = 0;
      }
    }
    // if ratio ends at end of line we have to do this check again before next
    // row.
    if (ratio > 0) {
      if (count == capacity) {
        capacity = capacity == 0 ? 8 : capacity * 2;
        gear_ratios =
            realloc(gear_ratios, sizeof(struct gear_ratio) * capacity);
      }
      gear_ratios[count++] = (struct gear_ratio){.col = matrix.cols - length,
                                                 .row = matrix.rows - 1,
                                                 .length = length,
                                                 .ratio = ratio};
      ratio = 0;
      length = 0;
    }
  }
  // printf("Total rows %d\n", matrix.rows);
  // printf("Total cols %d\n", matrix.cols);
  // matrix_print(&matrix);
  int result = 0;
  for (int row = 0; row < matrix.rows; row++) {
    for (int col = 0; col < matrix.cols; col++) {
      // skip positions in the mat
      if (!matrix.data[row][col]) {
        continue;
      }

      // for each symbol we check all gear ratios to see if we can find one that
      // would be touching the symbol
      int counter = 0;
      int product = 1;

      int min_x_symbol = col - 1;
      int max_x_symbol = col + 1;

      int min_y_symbol = row - 1;
      int max_y_symbol = row + 1;
      for (int i = 0; i < count; i++) {
        struct gear_ratio gr = gear_ratios[i];
        int min_x_gr = gr.col;
        int max_x_gr = gr.col + gr.length - 1;

        if (part_is_2_overlap_between_two_segements(min_x_symbol, min_x_gr,
                                                    max_x_symbol, max_x_gr) &&
            part_is_2_overlap_between_two_segements(min_y_symbol, gr.row,
                                                    max_y_symbol, gr.row)) {
          counter++;
          product *= gr.ratio;
        }
      }

      if (counter == 2) {
        result += product;
      }
    }
  }
  free(gear_ratios);
  matrix_free_rows(&matrix);
  free(matrix.data);
  return result;
}