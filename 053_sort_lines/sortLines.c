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

size_t readData(FILE * f, char ** data) {
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
    data = realloc(data, (count + 1) * sizeof(*data));
    data[count] = curr;
    curr = NULL;
    count++;
  }
  free(curr);
  return count;
}

void printData(char ** data, size_t count) {
  /* Do: printing out the strings in data, and free each of them right after printing */
  for (size_t i = 0; i < count; i++) {
    printf("%s", data[i]);
    free(data[i]);
  }
}

void allSteps(FILE * f) {
  char ** data = NULL;
  size_t count;

  // STEP 1 - read data,
  count = readData(f, data);
  // STEP 2 - sort,
  sortData(data, count);
  // STEP 3 - print
  printData(data, count);
  // STEP 4 - free memory
  free(data);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  FILE * f;

  // CASE 1: no input files, use stdin
  if (argc == 1) {
    f = stdin;
    allSteps(f);
  }
  // CASE 2: use input files
  else {  // argc > 1
    for (int i = 0; i < argc; i++) {
      f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "Error: File %s doesn't exist!\n", argv[i]);
        return EXIT_FAILURE;
      }
      allSteps(f);
    }
  }
  // STEP 5: exit successfully
  return EXIT_SUCCESS;
}
