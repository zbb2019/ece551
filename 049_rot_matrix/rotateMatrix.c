#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

void readMatrix(FILE * f, int ** oldMatrix) {
  /* Function 1
     This func read a matrix from f, and store it in oldMatrix,
     where oldMatrix[SIZE][SIZE] = {0};
  */
  int c;
  int count = 0;
  int row = 0;
  int col = 0;
  while ((c = fgetc(f)) != EOF) {
    count++;
    if (c != '\n') {
      // Address Error: more cols or rows
      if (row >= SIZE || col >= SIZE) {
        fprintf(stderr, "Error: input maxtrix is bigger than 10x10!\n");
        exit(EXIT_FAILURE);
      }
      // printf("%c\n", c);
      oldMatrix[row][col] = c;
      col++;
    }
    else if (col != SIZE) {  // when c == '\n'
      fprintf(stderr, "Error: input maxtrix doesn't have exactly 10 columns!\n");
      exit(EXIT_FAILURE);
    }
    else {  // when (c == '\n') and (col == SIZE)
      // printf("found new line\n");
      row++;
      col = 0;
    }
  }

  //Check Errors:
  if (count == 0) {
    fprintf(stderr, "Error: In file is empty!\n");
    exit(EXIT_FAILURE);
  }
  if (row != SIZE) {
    fprintf(stderr, "Error: Input matrix is less than 10 rows!\n");
    exit(EXIT_FAILURE);
  }
  return;
}
void rotate(int ** oldMatrix, int ** newMatrix) {
  /* Function 2
     This func rotates oldMatrix (in perfect SIZExSIZE) for 90deg in
     CW(clockwise)-direction, and store it into newMatrix (also in 
     perfect SIZExSIZE).
  */
  int i = 0;
  int j = 0;
  for (int col = SIZE - 1; col >= 0; col--) {
    for (int row = 0; row < SIZE; row++) {
      newMatrix[row][col] = oldMatrix[i][j];

      if (j == SIZE - 1) {
        i++;
        j = 0;
      }
      else {
        j++;
      }
    }
  }
  return;
}
void printMatrix(int ** matrix, size_t row, size_t col) {
  /* Function 3
     This function print matrix (row x col) into stdout.
   */
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      fprintf(stdout, "%c", matrix[i][j]);
    }
    fprintf(stdout, "\n");
  }
}

int main(int argc, char ** argv) {
  /* Main Function */

  // Address Error: empty/many argument
  if (argc != 2) {
    fprintf(stderr, "Error: Please passin exactly 1 inputFileName!\n");
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[1], "r");
  // Address Error: file not exists
  if (f == NULL) {
    fprintf(stderr, "Error: Files does NOT exist!\n");
    exit(EXIT_FAILURE);
  }

  // store the matrix from the file into: int oldMatrix[10][10]
  int old[SIZE][SIZE] = {0};
  int * oldMatrix[10] = {
      old[0], old[1], old[2], old[3], old[4], old[5], old[6], old[7], old[8], old[9]};
  readMatrix(f, oldMatrix);
  printf("Original 10x10 matrix:\n");
  //  printMatrix(oldMatrix, SIZE, SIZE);

  // rotate the matrix and store it into: int newMatrix[10][10]
  int new[SIZE][SIZE] = {0};
  int * newMatrix[10] = {
      new[0], new[1], new[2], new[3], new[4], new[5], new[6], new[7], new[8], new[9]};
  rotate(oldMatrix, newMatrix);
  printf("\nAfter rotation:\n");
  printMatrix(newMatrix, SIZE, SIZE);

  return EXIT_SUCCESS;
}
