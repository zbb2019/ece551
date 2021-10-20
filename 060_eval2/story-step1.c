#include <stdio.h>
#include <stdlib.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  /* STORY-STEP 1

     This program parses the story template by printing the story 
     and replacing blanks with the word "cat". 
 
     Inputs - 1 command line arguments: 
     1. the name of the file for the story template.  
  */

  // STEP 1 - check input errors
  checkArgc(argc, 2);
  FILE * f = fopen(argv[1], "r");
  checkFileExist(f, argv[1]);

  // STEP 2 - read the inputFile into an array of strings
  char ** lines = NULL;
  size_t sz = readFile(f, &lines);
  if (sz == 0) {
    fprintf(stderr, "Warning: the input file is empty");
    return EXIT_SUCCESS;
  }

  // STEP 3 - print file to stdout, with the blank replaced with words
  replaceNPrint(lines, sz, NULL, 0);

  // STEP 4 - close file
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close inputFile: %s\n", argv[1]);
    return EXIT_FAILURE;
  }
  // STEP 5 - free memory in lines
  freeLines(lines, sz);

  return EXIT_SUCCESS;
}
