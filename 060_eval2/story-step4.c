#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  /* STORY-STEP 4

     Inputs - 1 option ('-n') + 2 command line arguments: 
     1. the name of the file with the categories/words
     2. the name of the file for the story template. 

     This program makes use of the functions you wrote
     in previous steps (1, 2, 3), but adds optional 
     functionality to prevent the reuse of a word from a category. 
     That is, if the argument "-n" is given, the program ensures 
     that chooseWord will not return a word that has already been 
     used. Numbered blanks still reference a previously used word 
     as in step 3.    
  */

  // STEP 1 - check input errors + read files
  int option = 0;  // indicating no option '-n' passed in
  if (argc == 4) {
    if (strcmp(argv[1], "-n") == 0) {
      option = 1;
    }
    else {
      fprintf(stderr,
              "Usage: the option '%s' doesn't exist, please use '-n' only\n",
              argv[1]);
      return EXIT_FAILURE;
    }
  }
  else {
    checkArgc(argc, 3);
  }
  FILE * fcats = fopen(argv[1 + option], "r");  // open the file for category/words
  checkFileExist(fcats, argv[1 + option]);
  FILE * fstory = fopen(argv[2 + option], "r");  // open the file for story template
  checkFileExist(fstory, argv[2 + option]);

  //-----------------------organize catarray_t for category/words---------
  // STEP 2 - read category/words file into linesCats
  char ** linesCats = NULL;
  size_t szCats = readFile(fcats, &linesCats);
  if (szCats == 0) {
    fprintf(stderr, "Error: the input cat/word file is empty");
    return EXIT_FAILURE;
  }

  // STEP 3 - parsing each line of cat/words and store them into catarray_t
  catarray_t * cats = parsingWC(linesCats, szCats);

  // STEP 4 - print catarray_t - for testing
  //  printWords(cats);

  // STEP 5 - close file
  if (fclose(fcats) != 0) {
    fprintf(
        stderr, "Failed to close the category/words inputFile: %s\n", argv[1 + option]);
    return EXIT_FAILURE;
  }

  // -----------------parse & replace story template------------------
  // STEP 2 - read the story template file into linesStory
  char ** linesStory = NULL;
  size_t szStory = readFile(fstory, &linesStory);

  // STEP 3 - print story to stdout, with the blank replaced with words
  replaceNPrint(linesStory, szStory, cats, option);

  // STEP 4 - close story file
  if (fclose(fstory) != 0) {
    fprintf(
        stderr, "Failed to close the story template inputFile: %s\n", argv[2 + option]);
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
