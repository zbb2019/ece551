#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void store(char ** line_p, int stopPoint, char ** keyORvalue_p) {
  /* This func - 
     stores the string before stopPoint into the string keyORvalue (from *line_p) 
  */
  int j = 0;  // the size of the allocated array (that key or value points to)
  while (**line_p != stopPoint) {  // store all letters between '=' and '\n\0' (exlusive)
    *keyORvalue_p = realloc(*keyORvalue_p, (j + 1) * sizeof(**keyORvalue_p));
    (*keyORvalue_p)[j] = **line_p;
    (*line_p)++;
    j++;
  }
  *keyORvalue_p = realloc(*keyORvalue_p, (j + 1) * sizeof(**keyORvalue_p));
  (*keyORvalue_p)[j] = '\0';
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  /* Note: 
     malloc create an specified-size array of "something" in the heap, 
     meaning "something" is already declared, but still waiting to be initialized 
  */

  // STEP 1 - Open the file
  FILE * f = fopen(fname, "r");

  // data for read the lines of text
  char * line = NULL;
  char * lineCopy =
      NULL;       // use this pointer to move within the strings, so we can free(line);
  size_t linesz;  // size of the array allocated (getline's returnvalue = # of chars read)

  char * equalSign = NULL;  // a pointer to '='

  // data for the kvarray_t to return
  kvarray_t * ans = malloc(sizeof(*ans));
  ans->arr = NULL;
  size_t i = 0;  // = arrSize (use i for readability)

  // For READABILITY, set a pointer to the current working-on kvpair_t (key/value)
  kvpair_t * currPair = NULL;

  // STEP 2 - read the lines of text
  while (getline(&line, &linesz, f) >= 0) {
    lineCopy = line;

    // STEP 3+4 - split the lines into key/value pairs + add the pairs in to an array
    // 3a. find '=' in this line, and check error
    equalSign = strchr(line, '=');
    if (equalSign == NULL) {
      fprintf(stderr, "Error: the input line is not a key/value pair:\n\t%s\n", line);
      exit(EXIT_FAILURE);
    }

    // 4a. make 1 more space for a new kvpair_t (key/value pair) in the arr
    ans->arr = realloc(ans->arr, (i + 1) * sizeof(*(ans->arr)));
    currPair = &(ans->arr[i]);

    // 3b. store key into the pair
    currPair->key = NULL;
    store(&lineCopy, '=', &(currPair->key));
    lineCopy++;  //line was pointing to '=', so increment it

    // 3c. store value
    currPair->value = NULL;
    store(&lineCopy, '\n', &(currPair->value));

    i++;
  }
  free(line);

  // STEP 5 - close the file
  if (fclose(f) != 0) {
    fprintf(stderr, "Error: Failed to close the file \n");
    exit(EXIT_FAILURE);
  }
  // STEP 6 - return kvarray_t * that has my array
  ans->arrSize = i;
  return ans;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME

  /* This func free all memory alocated by "pairs" */
  for (size_t i = 0; i < pairs->arrSize; i++) {
    free((pairs->arr[i]).key);
    free((pairs->arr[i]).value);
  }
  free(pairs->arr);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME

  /* This func prints all pairs of key/value in "pairs" */
  for (size_t i = 0; i < pairs->arrSize; i++) {
    printf("key = '%s' value = '%s'\n", (pairs->arr[i]).key, (pairs->arr[i]).value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME

  /* This func searches for a matching key in "pairs".
     If found, returns the corresponding value;
     If no match is found, this function returns NULL. 
  */
  for (size_t i = 0; i < pairs->arrSize; i++) {
    if (strcmp((pairs->arr[i]).key, key) == 0) {
      return (pairs->arr[i]).value;
    }
  }
  return NULL;
}
