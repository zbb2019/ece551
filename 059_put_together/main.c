#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME

  /* This func takes a input file (containing a list of key) and a struct 
     kvarray_t (as the key/value look-up table), then
     compute the counts of the respected values (using key/value pairs),
     and store the results in a struct counts_t and return it.
*/
  FILE * f = fopen(filename, "r");
  counts_t * ans = createCounts();

  char * value = NULL;
  char * key = NULL;
  size_t keySize;
  ssize_t keyLen;
  while ((keyLen = getline(&key, &keySize, f)) >= 0) {
    // process the key so it doesn't have "\n" at the end
    if (key[keyLen - 1] == '\n') {
      key[keyLen - 1] = '\0';
      keyLen--;
    }

    // lookup the value wrt to the key
    value = lookupValue(kvPairs,
                        key);  // = NULL if the key is unknown/unfound in kvPairs
    addCount(ans, value);
  }
  free(key);

  if (fclose(f) != 0) {
    fprintf(stderr, "Error: Failed to close the input keysFile - %s\n", filename);
    exit(EXIT_FAILURE);
  }
  return ans;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {  // at least 3, programName + 1 kvInput + 1/more keysFile
    fprintf(stderr,
            "Error: missing input files, should be 1 kvInput + 1 or more keysFiles\n");
    return EXIT_FAILURE;
  }

  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  // printKVs(kv); //print for testing

  //count from 2 to argc (call the number you count i)
  counts_t * c;
  char * outName;
  FILE * f;
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    f = fopen(outName, "w");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "Error: Failed to close the outputfile - %s\n", outName);
      exit(EXIT_FAILURE);
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
