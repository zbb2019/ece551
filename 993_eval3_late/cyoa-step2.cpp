#include <assert.h>
#include <ctype.h>
#include <string.h>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "s2-page.hpp"

// MAIN
int main(int argc, char ** argv) {
  // STEP 1 - check the number of inputs
  if (argc != 2) {
    std::cerr << "cyoa-step 2: Need exactly 1 input directory!\n";
  }

  // STEP 2 - Read all the pages (belong to the story into a Story object)
  Story theStory;
  theStory.readAllPages(argv[1]);
  /*
  // checking step 2 by printing all pages in theStory
  theStory.printStoryToCheck();
  */

  // STEP 3 - Checking the story as a whole
  theStory.checkWholeStory();

  // STEP 4 - Play the game
  theStory.play();

  return EXIT_SUCCESS;
}
