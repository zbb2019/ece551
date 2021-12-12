#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

typedef enum wlc { WIN, LOSE, CHOICES, UNKNOWN } wlc_enum;

// class - Page
class Page {
 private:
  class Choice {
   public:
    size_t pn;
    std::string content;
    Choice(size_t pn, const std::string & str) : pn(pn), content(str) {}
  };
  size_t pageNumber;
  wlc_enum pageType;
  std::vector<Choice> choices;
  std::vector<std::string> storyText;

  std::string findPageType(std::istream & f) {
    /* This func determine the pageType of the input pagefile. */

    std::string currLine;
    if (!std::getline(f, currLine).eof()) {
      if (currLine == "WIN") {
        this->pageType = WIN;
      }
      else if (currLine == "LOSE") {
        this->pageType = LOSE;
      }
      else {
        this->pageType = CHOICES;
      }
      return currLine;
    }
    else {
      std::cerr << "Usage: Input page file is empty!" << std::endl;
      throw std::exception();
    }
  }

  Choice parseInputChoiceLine(std::string & currLine) {
    /* This func parse "24:Try to do blabla" into the number 24 and the text 
     "Try to do balbla" and store them into a Choice object */

    // check if it's an empty line ("\n" only)
    if (currLine == "") {
      std::cerr << "Error: Input Pagefile - Wrong format for the choices section!"
                << std::endl
                << "\t---- Found an empty line!" << std::endl;
      throw std::exception();
    }

    // check the existence of ":"
    size_t pos;
    if ((pos = currLine.find(":")) == std::string::npos) {  // CITE - string::find()
      std::cerr << "Error: Input Pagefile - Wrong format for the choices section!"
                << std::endl
                << "\t---- No colon found!" << std::endl;
      throw std::exception();
    }

    // check the number before ":"
    for (size_t i = 0; i < pos; i++) {
      if (isdigit(currLine[i]) == 0) {
        std::cerr << "Error: Input Pagefile - Wrong format for the choices section!"
                  << std::endl
                  << "\t---- Not pure numbers before the colon!" << std::endl;
        throw std::exception();
      }
    }

    // construct a choice object
    size_t pn;
    std::stringstream(currLine.substr(0, pos)) >> pn;
    // verify that (page# != 0), detect "page0.txt" given in this choice
    if (pn == 0) {
      std::cerr
          << "Error: One of the choice in the input page file is taking us to page0!"
          << std::endl;
      throw std::exception();
    }
    Page::Choice choice(pn,
                        currLine.substr(pos + 1));  // CITE - string::substr(pos, length)

    return choice;
  }

 public:
  Page(size_t pn, std::istream & f) :
      pageNumber(pn),
      pageType(UNKNOWN),
      choices(),
      storyText() {
    /* This constructor takes pn (the page#) and f (the istream to the input page file),
       and creat a page object.
     */

    // Part 1 - store WIN/LOSE/Choices
    std::string currLine = this->findPageType(f);
    if (this->pageType == CHOICES) {
      do {
        Choice c = this->parseInputChoiceLine(currLine);
        this->choices.push_back(c);
      } while (!std::getline(f, currLine).eof() && currLine[0] != '#');
    }  // if there's #, it gets every line before #; if no #, it gets to .eof
    else {
      std::getline(f, currLine);
    }

    // Part 2 - check line #...
    if (currLine[0] != '#') {  // It's at the end of the file, but still didn't find #
      std::cerr << "Error: Input Pagefile ---- " << std::endl
                << "\tCASE I - CHOICE page - Didn't find the #-line throughout the "
                   "entire file!"
                << std::endl
                << "\tCASE II - WIN/LOSE page - no #-line right after WIN/LOSE!"
                << std::endl;
      throw std::exception();
    }

    // Part 3 - Story's text
    if (std::getline(f, currLine).eof()) {  // ???
      std::cerr << "Error: Input Pagefile - No existing text for storyText section!"
                << std::endl;
      throw std::exception();
    }
    else {
      do {
        storyText.push_back(currLine);
      } while (!std::getline(f, currLine).eof());
    }
  }

  void printChoicesTU() {
    /* This func print the list of choices given from the input page 
       file, in the following format 
       (Note: 
       1. choices should be listed in same order as in the input file
       2. don't show the resulting page# that each choice will lead to
       ):
       

       What would you like to do?

       _1. The text of the choice
       _2. The text of the choice
       _3. The text of the choice
    */

    std::cout << "What would you like to do?" << std::endl << std::endl;

    int count = 1;
    for (std::vector<Choice>::iterator it = this->choices.begin();
         it != this->choices.end();
         ++it) {
      std::cout << " " << count << ". " << it->content << std::endl;
      // don't need (this part) in actual output
      // std::cout << " (--> go to page#" << it->pn << ")" << std::endl;
      count++;
    }
  }

  void printStoryTextTU() {
    /* This func print the storyText part exactly the same as in the input 
       page file, without adding any addition stuff ---- such as "\n".
    */

    for (std::vector<std::string>::iterator it = this->storyText.begin();
         it != this->storyText.end();
         ++it) {
      std::cout << *it << std::endl;
    }
  }

  void printPageTU() {
    /* This func display a page To User. */

    // 1. print storyText
    this->printStoryTextTU();
    std::cout << std::endl;

    // 2. print the WIN/LOST-Message or the choices
    if (pageType == WIN) {
      std::cout << "Congratulations! You have won. Hooray!" << std::endl;
    }
    else if (pageType == LOSE) {
      std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
    else if (pageType == CHOICES) {
      this->printChoicesTU();
    }
    else if (pageType == UNKNOWN) {
      std::cerr << "Error: PageType = UNKNOWN" << std::endl;
      throw std::exception();
    }
    else {
      std::cerr << "Error: PageType != any of the assigned values, but =" << pageType
                << std::endl;
      throw std::exception();
    }
  }

  void printInputPageSampleCheck() {
    /* This func should print the pageNumber and pageType, then print a 
       sample of what's exactly written in the input page file, to show that 
       everything is stored correctly into the page class.
     */

    std::cout << std::endl
              << std::endl
              << "-----------------------printPageinfocheck for page#" << this->pageNumber
              << "-----------------------" << std::endl;

    if (pageType == WIN) {
      std::cout << "WIN" << std::endl;
    }
    else if (pageType == LOSE) {
      std::cout << "LOSE" << std::endl;
    }
    else if (pageType == CHOICES) {
      for (std::vector<Choice>::iterator it = this->choices.begin();
           it != this->choices.end();
           ++it) {
        std::cout << it->pn << ":" << it->content << std::endl;
      }
    }
    else if (pageType == UNKNOWN) {
      std::cerr << "Error: PageType = UNKNOWN" << std::endl;
      throw std::exception();
    }
    else {
      std::cerr << "Error: PageType != any of the assigned values, but =" << pageType
                << std::endl;
      throw std::exception();
    }

    std::cout << "#" << std::endl;
    this->printStoryTextTU();

    std::cout << "------------------------printPageinfocheck ends------------------------"
              << std::endl
              << std::endl
              << std::endl;
  }
};
