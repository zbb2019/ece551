#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "funcs.cpp"
typedef enum wlc { WIN, LOSE, CHOICES, UNKNOWN } wlc_enum;

class Page {
 private:
  class Choice {
   private:
    size_t pageNumber;
    std::string content;

   public:
    Choice(size_t pn, ) : pageNumber()
  };

 public:
  size_t pageNumber;
  wlc_enum pageType;
  std::vector<Choice> choices;
  std::vector<std::string> storyText;

  Page(size_t pn, std::istream & f) :
      pageNumber(pn),
      pageType(UNKNOWN),
      choices(std::vector<Choice>()),
      storyText(std::vector<std::string>()) {
    // Part 1 - WIN/LOSE/Choices
    pageType = findPageType(f);
    std::string currLine;
    while (!std::getline(f, currLine).eof() && currLine[0] != '#') {
      Choice c = parseInputChoiceLine(currLine);
      choices.push_back(c);
    }

    // Part 2 - #...

    // Part 3 - Story's text
  }

  friend
};
