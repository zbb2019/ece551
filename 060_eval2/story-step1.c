#include <stdio.h>
#include <stdlib.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  /* This program should parse the story template by printing the story 
     and replacing blanks with the word "cat". 
  
     Input: 1 command line argument - the file to read the story template from. 
  */

  // STEP 1 - check input errors
  checkArgc(argc, 2);
  FILE * f = fopen(argv[1], "r");
  checkFileExist(f);

  // STEP 2 - read the inputFile into an array of strings
  char ** lines = NULL;
  size_t sz = readFile(f, &lines);

  // STEP 3 - print file to stdout, with the blank replaced with words
  replaceNPrint(lines, sz);

  // STEP 4 - close file
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close inputFile: %s\n", argv[1]);
    return EXIT_FAILURE;
  }
  // STEP 5 - free memory in lines
  freeLines(lines, sz);

  return EXIT_SUCCESS;
}
