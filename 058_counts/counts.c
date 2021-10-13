#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  counts->arr = NULL;
  counts->arrSize = 0;
  counts->unknownTimes = 0;
  return counts;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  // CASE 1: name is unknown
  if (name == NULL) {
    (c->unknownTimes)++;
    return;
  }

  // CASE 2: this name already exist in our record
  for (size_t i = 0; i < c->arrSize; i++) {
    if (strcmp((c->arr[i]).name, name) == 0) {
      ((c->arr[i]).times)++;
      return;
    }
  }

  // CASE 3: it's a new name, we need to add to our array
  c->arr = realloc(c->arr, (c->arrSize + 1) * sizeof(*(c->arr)));
  (c->arr[c->arrSize]).times = 1;

  (c->arr[c->arrSize]).name =
      malloc((strlen(name) + 1) * sizeof(*(c->arr[c->arrSize]).name));
  strcpy((c->arr[c->arrSize]).name, name);

  c->arrSize++;
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->arrSize; i++) {
    fprintf(outFile, "%s: %d\n", (c->arr[i]).name, (c->arr[i]).times);
  }
  if (c->unknownTimes != 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unknownTimes);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->arrSize; i++) {
    free((c->arr[i]).name);
  }
  free(c->arr);
  free(c);
}
