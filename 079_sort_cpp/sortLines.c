#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void printData(char ** data, size_t count) {
  /* Do: printing out the strings in data, and free each of them 
     right after printing */
  if (data == NULL) {
    fprintf(stderr, "Error: data = NULL");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < count; i++) {
    printf("%s", data[i]);
  }
}

size_t readData(FILE * f, char *** dataPointer) {
  /* Input: FILE * f - where to read the strings,
              char ** data - an array to store the strings;
     Output: size_t count - the number of strings contained in char ** data;
     Do: read each line in "f" as a string, and store them in "data" 
           as counting the number of strings
  */
  char * curr = NULL;
  size_t sz;
  size_t count = 0;

  while (getline(&curr, &sz, f) >= 0) {
    *dataPointer = realloc(*dataPointer, (count + 1) * sizeof(**dataPointer));
    (*dataPointer)[count] = curr;
    curr = NULL;
    count++;
  }
  if (curr != NULL) {
    free(curr);
  }
  // address empty input/file
  if (count == 0) {
    fprintf(stderr, "Error: Empty input(file)!\n");
    exit(EXIT_FAILURE);
  }
  return count;
}

void allSteps(FILE * f) {
  char ** data = NULL;
  size_t count;

  // STEP 1 - read data,
  count = readData(f, &data);
  // STEP 2 - sort,
  sortData(data, count);

  // STEP 3 - print
  printData(data, count);

  // STEP 4 - free memory
  for (int i = 0; i < count; i++) {
    free(data[i]);
  }
  free(data);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  FILE * f;
  int c = -1;

  // CASE 1: no input files, use stdin
  if (argc == 1) {
    f = stdin;
    allSteps(f);
  }
  // CASE 2: use input files
  else {  // argc > 1
    for (int i = 1; i < argc; i++) {
      f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "Error: File %s doesn't exist!\n", argv[i]);
        return EXIT_FAILURE;
      }
      allSteps(f);
      c = fclose(f);
      if (c != 0) {
        fprintf(stderr, "Error: Failed to close the file %s\n", argv[i]);
        return EXIT_FAILURE;
      }
    }
  }
  // STEP 5: exit successfully
  return EXIT_SUCCESS;
}
