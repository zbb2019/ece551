#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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

void printData(std::vector<std::string> & data) {
  std::vector<std::string>::iterator it = data.begin();
  while (it != data.end()) {
    std::cout << *it << "\n";
    ++it;
  }
}
void allSteps(std::istream & f) {
  std::vector<std::string> data;

  // STEP 1 - read data,
  data = readData(f, data);
  // STEP 2 - sort,
  std::sort(data.begin(), data.end());

  // STEP 3 - print
  printData(data);
}

int main(int argc, char ** argv) {
  // CASE 1: no input files, use stdin
  if (argc == 1) {
    allSteps(std::cin);
  }
  // CASE 2: use input files
  else {  // argc > 1
    std::ifstream f;
    for (int i = 1; i < argc; i++) {
      f.open(argv[i]);
      if (!f.is_open()) {
        std::cerr << "Error: File " << argv[i] << " doesn't exist!\n";
        return EXIT_FAILURE;
      }
      allSteps(f);
      f.close();
    }
  }
  // STEP 5: exit successfully
  return EXIT_SUCCESS;
}
