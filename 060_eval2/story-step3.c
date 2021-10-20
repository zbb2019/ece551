#include <stdio.h>
#include <stdlib.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  /* Inputs - 2 command line arguments: 
     1. the name of the file with the categories/words
     2. the name of the file for the story template. 

     This program should make use of the functions you wrote for 
     step 1 and step 2, but it should add the functionality to:
     1) randomly choose a word from the named category to replace each 
     blank 
     2) support references to previously used words.
    
  */

  // STEP 1 - check input errors + read files
  checkArgc(argc, 3);
  FILE * fcats = fopen(argv[1], "r");  // open the file for category/words
  checkFileExist(fcats, argv[1]);
  FILE * fstory = fopen(argv[2], "r");  // open the file for story template
  checkFileExist(fstory, argv[2]);

  //-----------------------organize catarray_t for category/words---------
  // STEP 2 - read category/words file into linesCats
  char ** linesCats = NULL;
  size_t szCats = readFile(fcats, &linesCats);

  // STEP 3 - parsing each line of cat/words and store them into catarray_t
  catarray_t * cats = parsingWC(linesCats, szCats);

  // STEP 4 - print catarray_t - for testing
  //  printWords(cats);

  // STEP 5 - close file
  if (fclose(fcats) != 0) {
    fprintf(stderr, "Failed to close the category/words inputFile: %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  // -----------------parse & replace story template------------------
  // STEP 2 - read the story template file into linesStory
  char ** linesStory = NULL;
  size_t szStory = readFile(fstory, &linesStory);

  // STEP 3 - print story to stdout, with the blank replaced with words
  replaceNPrint(linesStory, szStory, cats);

  // STEP 4 - close story file
  if (fclose(fstory) != 0) {
    fprintf(stderr, "Failed to close the story template inputFile: %s\n", argv[2]);
    return EXIT_FAILURE;
  }

  // ------------------free all memory------------------------------
  // STEP 5 - free linesStory
  freeLines(linesStory, szStory);
  // STEP 6 - free linesCats & cats
  freeLines(linesCats, szCats);
  freeCatarray_t(cats);

  return EXIT_SUCCESS;
}
