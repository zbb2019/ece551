#include <assert.h>
#include <ctype.h>
#include <string.h>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "page.hpp"

size_t parseCheckPageFilename(char * filename) {
  /* This func parse the page's filename,
     check whether the format of filename is correct,
     and return the pageNumber,
     
   */

  // 1. check if filename is in format of "page___.txt"
  char * dot = strchr(filename, '.');
  if (strncmp(filename, "page", 4) != 0 || dot == NULL || strcmp(dot, ".txt") != 0) {
    std::cerr << "Usage: Incorrect pagefile format (should be page___.txt): " << filename
              << std::endl;
    throw std::exception();
  }

  // 2. verify the ___ in page___.txt are all digits (i.e. page# is an int >= 0)
  //    and store it into a string <pn_str>
  char * number = filename + 4;
  std::string pn_str;
  while (number != dot) {
    if (isdigit(*number) == 0) {  // if ___ contains any NON-digit (0-9) char
      std::cerr << "Usage: Incorrect pagefile format (should be page_.txt, where _ is a "
                   "positive integer): "
                << filename << std::endl;
      throw std::exception();
    }
    pn_str.push_back(*number);
    number++;
  }

  // 3. convert the page# from <pn_str> into a size_type <pn>
  size_t pn;
  std::stringstream(pn_str) >> pn;

  // 4. verify that (page# != 0), detect "page0.txt"
  if (pn == 0) {
    std::cerr << "Usage: Cannot take page0.txt OR " << filename
              << " as the input page file!" << std::endl;
    throw std::exception();
  }

  return pn;
}

void allSteps(size_t pn, std::istream & f) {
  // Step 1 - read and store the page into a Page object
  Page onePage(pn, f);

  // Step 2 - check the new  page object by printing a re-created input page file
  // onePage.printInputPageSampleCheck();
  // std::cout << "-----------------------Now print the page in the format TU !"
  //          << "-----------------------" << std::endl;

  // Step 3 - print the page in the format To User
  onePage.printPageTU();
}

int main(int argc, char ** argv) {
  // check the number of inputs
  if (argc != 2) {
    std::cerr << "cyoa-step 1: Need exactly 1 input file!\n";
  }

  // parse inputfilename to pageNumber while checking its error
  size_t pn = parseCheckPageFilename(argv[1]);

  // open the input page file
  std::ifstream f;
  f.open(argv[1]);
  if (!f.is_open()) {
    std::cerr << "Error: File " << argv[1] << " doesn't exist!\n";
    throw std::exception();
  }

  // allsteps
  allSteps(pn, f);

  // close page file
  f.close();

  return EXIT_SUCCESS;
}
