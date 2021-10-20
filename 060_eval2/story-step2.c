#include <stdio.h>
#include <stdlib.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  /* STORY-STEP 2

     Input: one command line argument - the name of the file with the 
     categories and words. 
     
     This program reads from the input file and store the words into 
     a catarray_t and print them using the provided function printWords.
  */

  // STEP 1 - check input errors
  checkArgc(argc, 2);
  FILE * f = fopen(argv[1], "r");
  checkFileExist(f, argv[1]);

  // STEP 2 - read file into lines
  char ** lines = NULL;
  size_t sz = readFile(f, &lines);

  // STEP 3 - parsing each line and store them into catarray_t
  catarray_t * cats = parsingWC(lines, sz);

  // STEP 4 - print catarray_t
  printWords(cats);

  // STEP 5 - close file
  fclose(f);

  // STEP 6 - free memory
  freeLines(lines, sz);
  freeCatarray_t(cats);

  return EXIT_SUCCESS;
}
