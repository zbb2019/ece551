#include <assert.h>
#include <ctype.h>
#include <string.h>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "aPage.hpp"

std::vector<std::string> & readData(std::istream & f, std::vector<std::string> & data) {
  /* Input: istream & f - where to read the strings,
              std::vector<std::string> & data - an array to store the strings;
     Output: std::vector<std::string> & - an array to store the strings; 
     Do: read each line in "f" as a string, and store them in "data" 
           as counting the number of strings
  */

  std::string curr;

  while (!std::getline(f, curr).eof()) {
    data.push_back(curr);
  }
  // address empty input/file
  if (data.size() == 0) {
    fprintf(stderr, "Error: Empty input(file)!\n");
    exit(EXIT_FAILURE);
  }
  return data;
}

void allSteps(size_t pn, std::istream & f) {
  // Step 1 - read and store the page into Object Page
  Page onePage(pn, f);
  // Step 2 - check error in the page

  // Step 3 - print the page in format to the user
}

size_t parseFilename(char * filename) {
  /* This func parse the page's filename and return the pageNumber
   */

  // 1. check if filename is in format of "page___.txt"
  char * dot = strchr(filename, '.');
  if (dot == NULL || strncmp(filename, "page", 4) != 0 || strcmp(dot, ".txt") != 0) {
    std::cerr << "Usage: Incorrect pagefile format (should be page_.txt): " << filename
              << std::endl;
    throw std::exception();
  }

  // 2. check ___ in page___.txt are all digits (meaning page# is 0 or a positive int)
  char * number = filename + 4;
  std::string pn_str;
  while (number != dot) {
    if (isdigit(*number) == 0) {  // if ___ contains NON-digit char
      std::cerr << "Usage: Incorrect pagefile format (should be page_.txt): " << filename
                << std::endl;
      throw std::exception();
    }
    pn_str.push_back(*number);
    number++;
  }

  std::cout << "Its page number is: " << pn_str << std::endl;
  size_t ans = std::stoi(pn_str);  // CITE - std::stoi()
  return ans;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "cyoa-step 1: Need only 1 input file!\n";
  }

  // parse filename to pageNumber + check error
  size_t pn = parseFilename(argv[1]);

  // open page file
  std::ifstream f;
  f.open(argv[1]);
  if (!f.is_open()) {
    std::cerr << "Error: File " << argv[1] << " doesn't exist!\n";
  }

  allSteps(pn, f);

  // close page file
  f.close();
  return EXIT_SUCCESS;
}
