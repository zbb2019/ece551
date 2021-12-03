#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "aPage.hpp"

wlc_enum findPageType(std::istream & f) {
  /* This func determine the pageType of the input pagefile. */

  std::string currLine;
  if (!std::getline(f, currLine).eof()) {
    if (currLine == "WIN") {
      return WIN;
    }
    else if (currLine == "LOSE") {
      return LOSE;
    }
    else {
      return CHOICES;
    }
  }
  else {
    std::cerr << "Usage: Input page file is empty!" << std::endl;
    throw std::exception();
    //return UNKNOWN;
  }
}
Choice parseInputChoiceLine(std::string & currLine) {
  /* This func parse "24:Try to do blabla" into the number 24 and the text 
     "Try to do balbla" and store them into a Choice object */

  // check the existence of ":"
  size_t pos;
  if ((pos = currLine.find(":")) == std::string::npos) {  // CITE - string::find()
    std::cerr << "Error: Input Pagefile - Wrong format for choices!" << std::endl;
    throw std::exception();
  }

  // check the number before ":"
  for (size_t i = 0; i < pos; i++) {
    if (isdigit(currLine[i]) == 0) {
      std::cerr << "Error: Input Pagefile - Wrong format for choices!" << std::endl;
      throw std::exception();
    }
  }

  Page::Choice choice();
  choice.pageNumber =
      std::stoi(currLine.substr(0, pos));  // CITE - string::substr(pos, length)
}
