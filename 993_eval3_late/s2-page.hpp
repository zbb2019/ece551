#include <string.h>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

typedef enum wlc { WIN, LOSE, CHOICES, UNKNOWN } wlc_enum;

// ---------------------------------------class - Page----------------------------------------
class Page {
 private:
  // Member class
  class Choice {
   public:
    size_t pn;
    std::string content;
    Choice(size_t pn, const std::string & str) : pn(pn), content(str) {}
  };

  // private fields
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
  // Page - constructor
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

  // getPageNumber
  size_t getPageNumber() { return this->pageNumber; }

  // getPageType
  wlc_enum getPageType() { return this->pageType; }

  // printChoicesTU
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

  // printStoryTextTU
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

  // printPageTU
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

  // printInputPageSampleCheck
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

  // checkAllReferredPNs - part A for checking whole story's condition
  void checkAllReferredPNs(size_t storySize) {
    /* This func checks that:
       In each CHOICE page, each choice refers to a pageNumber to go to,
       this pageNumber must be valid in theStory
     */

    if (pageType == CHOICES) {
      for (std::vector<Choice>::iterator it = choices.begin(); it != choices.end();
           ++it) {
        if (it->pn > storySize) {  // page# must be <= story.size,
          // don'need to check (page# <=0) now, b/c it was checked during Page-construction
          std::cerr << "Error in Story - CASE A:" << std::endl
                    << "\tOne choice in a CHOICE page refers to a NON-existing page!"
                    << std::endl;
          throw std::exception();
        }
      }
    }
  }

  // checkChoicesContainMyPN - part B for checking whole story's condition
  bool checkChoicesContainMyPN(size_t myPageNumber) {
    /* This func checks whether this page contains a referral to the given pageNumber.
       If yes, return true; else, return false.
       If this page is not a CHOICE-type page, return false.
     */

    if (pageType == CHOICES) {
      for (std::vector<Choice>::iterator it = choices.begin(); it != choices.end();
           ++it) {
        // for each choice in this page
        if (it->pn == myPageNumber) {
          return true;
        }
      }
      return false;
    }
    return false;
  }

  // printChoicesNumbersHelper
  std::string printChoicesNumbersHelper() const {
    /* For the following options, this func prints: "1 or 2 or 3"
      
      What would you like to do?
       _1. The text of the choice
       _2. The text of the choice
       _3. The text of the choice
    */

    std::stringstream ans;
    size_t count = choices.size();
    for (size_t i = 1; i < count; i++) {  // count = 3, i = 1, 2
      ans << i << " or ";
    }
    ans << count;
    return ans.str();
  }

  // checkUserChoiceInput
  bool checkUserChoiceInputValid(std::string & choiceAnswer) const {
    // for input "choiceAnswer", invalid include the following cases:

    // 1. containing any char that's not a digit (i.e. needs to be an integer >=0 )
    for (std::string::iterator it = choiceAnswer.begin(); it != choiceAnswer.end();
         ++it) {
      if (isdigit(*it) == 0) {
        return false;
      }
    }

    // 2. is not in range of [1, total_number_of_choices]
    size_t choiceNumber;
    std::stringstream(choiceAnswer) >> choiceNumber;
    if (choiceNumber < 1 || choiceNumber > choices.size()) {
      return false;
    }

    return true;
  }

  // inputFromUser
  size_t inputFromUser() const {
    /* This func get a valid input from user - for their decision on choice No. by doing:
       1. reads a positive integer from user for their decision on choices 
       2. check its validity (it's valid if the input>0 && 
                              it's one of the given choice No. in this page)
       3. If invalid, re-input until it's valid.
       4. Finally, convert the valid input into size_t
    */

    // 1.
    std::string choiceAnswer;
    getline(std::cin, choiceAnswer);

    // 2. + 3.
    while (this->checkUserChoiceInputValid(choiceAnswer) == false) {
      std::cout << "!!!Invalid input: You much input exactly "
                << this->printChoicesNumbersHelper() << "!" << std::endl
                << "\tDon't type anything else! Not even an extra whitespace!"
                << std::endl
                << "\tTry again:" << std::endl;
      getline(std::cin, choiceAnswer);
    }

    // 4. convert into size_1
    size_t choiceNumber;
    std::stringstream(choiceAnswer) >> choiceNumber;

    return choiceNumber;
  }

  // getPnOfGivenChoice
  size_t getPnOfGivenChoice(size_t inputChoiceNumber) const {
    return (this->choices[inputChoiceNumber - 1]).pn;
  }
};

// ---------------------------------------class - Story----------------------------------------
class Story {
 private:
  size_t size;
  std::vector<Page> allPages;

 public:
  // Story - constructor
  Story() : size(0), allPages() {}

  // addOnePage
  void addOnePage(const Page & rhs) {
    this->allPages.push_back(rhs);
    size++;
  }

  // readCheckOnePage
  void readCheckOnePage(size_t pn, std::istream & f) {
    /* Given a pageNumber (pn) and its .txt file (f), this func 
     reads + check + create this page into a Page object.
     Then it stores this Page object into the given Story object.
  */

    Page onePage(pn, f);
    this->addOnePage(onePage);
  }

  // calcPathName
  std::string calcPathName(const char * dirName, size_t pn) const {
    //  std::stringstream pn_stream;
    //  pn_stream << pn;

    std::stringstream pathName;
    if (dirName[strlen(dirName) - 1] == '/') {
      pathName << dirName << "page" << pn << ".txt";
      //    std::cout << "Verify ---- dirName contains /, so pathName is " << pathName.str()
      //        << std::endl;
    }
    else {
      pathName << dirName << "/page" << pn << ".txt";
    }
    return pathName.str();
  }

  // readAllpages
  void readAllPages(const char * dirName) {
    /* This func read all the pages belong to the story, store each page into a page object.
     Then, store each page object into the given story object.
 
     It first try to open page1, then page2, page3, ....
   */

    std::ifstream f;
    size_t pn = 1;
    std::string pathName = this->calcPathName(dirName, pn);
    f.open(pathName.c_str());  // CITE - c_str() convert string to char *
    while (f.is_open()) {
      // read + check + store 1 page in to theStory
      this->readCheckOnePage(pn, f);

      // close page file
      f.close();

      // looking for the next page
      pn++;
      pathName = this->calcPathName(dirName, pn);
      f.open(pathName.c_str());  // CITE - c_str() convert string to char *
    }

    // check if page1 exists
    if (pn == 1) {
      std::cerr << "Usage: page1.txt don't exist!" << std::endl;
      throw std::exception();
    }
  }

  // printStoryCheck
  void printStoryToCheck() {
    std::cout << "Now printing out each page in theStory for checking purposes. "
              << std::endl
              << std::endl;

    for (std::vector<Page>::iterator it = allPages.begin(); it != allPages.end(); ++it) {
      std::cout << "----------------------------page#" << it->getPageNumber()
                << "------------------------------" << std::endl;
      it->printPageTU();
      std::cout << "--------------------------------------------------------------"
                << std::endl
                << std::endl
                << std::endl;
    }
  }

  // cwspA - checkWholeStory Part-a
  void cwspA() {
    // check each page
    for (std::vector<Page>::iterator it = allPages.begin(); it != allPages.end(); ++it) {
      it->checkAllReferredPNs(this->size);
    }
  }

  // cwspB - checkWholeStory Part-b
  void cwspB() {
    for (std::vector<Page>::iterator curr = allPages.begin(); curr != allPages.end();
         ++curr) {
      // for each page "curr", EXCEPT page#1:
      if (curr == allPages.begin()) {
        continue;
      }

      // check whether there's any "other" page refers to curr, except itself
      bool result = false;
      for (std::vector<Page>::iterator other = allPages.begin(); other != allPages.end();
           ++other) {
        if (other != curr) {
          if (other->checkChoicesContainMyPN(curr->getPageNumber()) == true) {
            result = true;
            break;
          }
        }
      }

      // after searching for page "curr" in all "other" pages, check whether we find it
      if (result == false) {
        std::cerr << "Error in Story - CASE B:" << std::endl
                  << "\tFound no page that refers to Page#" << curr->getPageNumber()
                  << "!" << std::endl;
        throw std::exception();
      }
    }
  }

  // pageTypeToStringConverter
  std::string pageTypeToStringConverter(wlc_enum pageType) const {
    if (pageType == WIN) {
      return "WIN";
    }
    else if (pageType == LOSE) {
      return "LOSE";
    }
    else if (pageType == CHOICES) {
      return "CHOICES";
    }
    else if (pageType == UNKNOWN) {
      return "UNKNOWN";
    }
    else {
      return "Non-Existing-pageType";
    }
  }

  // cwspCD - checkWholeStory Part-c&d
  void cwspCD(wlc_enum pageType) {
    /* This page verify whether this story contains page of the given pageType.
       If no, it wil report error and throw exceptions.
     */

    // check each page
    for (std::vector<Page>::iterator it = allPages.begin(); it != allPages.end(); ++it) {
      if (it->getPageType() == pageType) {
        return;
      }
    }

    // didn't find any page of the given "pageType"

    std::cerr << "Error in Story - CASE C:" << std::endl
              << "\tDid not find any " << this->pageTypeToStringConverter(pageType)
              << " page in this story!" << std::endl;
    throw std::exception();
  }

  // checkWholeStory
  void checkWholeStory() {
    /* Checking the story's condition as a whole:
     a. each choice (in each CHOICE page) refers to a pageNumber to go to,
        this pageNumber must be valid in theStory
     b. each page (EXCEPT page#1!!!) has to be referred from another page
     c. at least 1 WIN page exists
     d. at least 1 LOSE page exists
   */

    this->cwspA();
    this->cwspB();
    this->cwspCD(WIN);
    this->cwspCD(LOSE);
  }

  // play
  void play() {
    /* This func plays the story game. */

    /*
      // display "Now the story begins..."
      std::cout << std::endl
              << std::endl
              << std::endl
              << "############################Now the story "
                 "begins...##############################"
              << std::endl;
    */

    Page * currPage = &(allPages[0]);  //start on page1
    while (currPage != NULL) {
      // 1. display this page
      currPage->printPageTU();

      // 2. if it's a WIN/LOSE page, exit successly
      if (currPage->getPageType() == WIN || currPage->getPageType() == LOSE) {
        currPage = NULL;
        return;
      }

      // 3. get a valid input from user - for their decision on choice No.
      size_t input = currPage->inputFromUser();
      /*
      // display user's input choice + "--> going to next page... ----"
      std::cout << std::endl
                << "---- You chose choice No. " << input << " --> going to next page... ----"
                << std::endl;
      */

      // 4. get to next page corresponding to user's input
      size_t nextPageNumber = currPage->getPnOfGivenChoice(input);
      currPage = &(allPages[nextPageNumber - 1]);
    }
  }
};
