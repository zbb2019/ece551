#include "rand_story.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkArgc(int argc, int expectArgc) {
  /* This func check whether the number of command line input arguments (from main.c) 
     is equal to the expected number. 
  */

  if (argc != expectArgc) {
    fprintf(stderr, "Usage: Not exactly %d input file(s)!\n", expectArgc - 1);
    exit(EXIT_FAILURE);
  }
}

void checkFileExist(FILE * f, char * filename) {
  /* This func check whether the file we opened exists or not. */
  if (f == NULL) {
    fprintf(stderr, "Usage: the input file '%s' doesn't exist!\n", filename);
    exit(EXIT_FAILURE);
  }
}

size_t readFile(FILE * f, char *** linesp) {
  /* This func store all the lines from a file into an array of strings (1 line per string)
     
     Inputs: 
     FILE * f - the file to read lines from
     char *** linesp - a pointer to the array of strings, where to store the lines 
     
     Output: size_t i - the size of the array (*linesp)
  */

  char * curr = NULL;
  size_t linecap;
  size_t i = 0;

  while (getline(&curr, &linecap, f) >= 0) {
    *linesp = realloc(*linesp, (i + 1) * sizeof(**linesp));
    (*linesp)[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);

  // check empty file
  if (i == 0) {
    fprintf(stderr, "Error: the input file is empty");
    exit(EXIT_FAILURE);
  }

  return i;
}

char * copyPartialString(char ** start, char * end, int nullTerminatorYN) {
  /* This func copy a specified part of a string into an empty string, and add '\0' according
     to specification.
     
     Input:
     char ** start - a pointer to a pointer to the starting char in the string (copy inclusively)
     char * end - a pointer to the ending char in the string (copy exclusively)
     int nullterminatoryn - =1 if need to add '\0', else =1 

     Output:
     char * - a pointer to the duplicated string stored in heap
   */

  int length = end - *start + nullTerminatorYN;  //nullTerminatorYN = 1(yes) or 0(no)
  char * ans = malloc(length * sizeof(*ans));
  for (int i = 0; i < (length - nullTerminatorYN); i++) {
    ans[i] = **start;
    (*start)++;
  }
  if (nullTerminatorYN == 1) {
    ans[length - 1] = '\0';
  }
  (*start)++;  // now the string starts right after 'char * end'
  return ans;
}

void storeWord(category_t * cat, const char * word) {
  /* This func store a word to the struct, which category_t * cat points to */
  cat->words = realloc(cat->words, (cat->n_words + 1) * sizeof(*(cat->words)));
  cat->words[cat->n_words] =
      malloc((strlen(word) + 1) * sizeof(*(cat->words[cat->n_words])));
  strcpy(cat->words[cat->n_words], word);
  cat->n_words++;
}

int checkPosInt(char * category) {
  /* This func checks if category is a positive integer 
     (i.e. all chars are digits, but !=0), and return 1 if yes;
     return 0 if no
 */
  size_t sz = strlen(category);
  for (size_t i = 0; i < sz; i++) {
    if (isdigit(category[i]) == 0) {  // if = 0, not a digit
      return 0;
    }
  }

  if (atoi(category) == 0) {
    return 0;
  }

  return 1;
}

const char * findPreviousWord(category_t * usedp, size_t index) {
  /* This func find and return the specified previously written word,
     which is stored in 'category_t * usedp', according to  the given index.
   */
  if (index < 1) {
    fprintf(stderr, "Error: the given category name contains a integer < 1\n");
    exit(EXIT_FAILURE);
  }
  else if (index > usedp->n_words) {
    fprintf(stderr,
            "Error: the story wants to write the %zu-th previous written word,\n"
            "\tbut we have only written %zu words so far.\n",
            index,
            usedp->n_words);
    exit(EXIT_FAILURE);
  }
  return usedp->words[usedp->n_words - index];
}

void freeLines(char ** lines, size_t sz) {
  /* This func frees the input array of strings.
     
     Inputs:
     char ** lines - the array of strings to free
     size_t sz - the size of 'lines'


     Output: void
   */

  for (size_t i = 0; i < sz; i++) {
    free(lines[i]);
  }
  free(lines);
}

int lookupCategory(catarray_t * source, char * category) {
  /* This func take a pointer to catarray_t and a category (char *), and check 
     whether the catarray_t already contain this category. If yes, return the 
     index (i) of the matching category_t; else, return -1. 
   */
  for (size_t i = 0; i < source->n; i++) {
    if (strcmp((source->arr[i]).name, category) == 0) {
      return i;
    }
  }
  // if not found
  return -1;
}

int lookupWord(category_t * source, char * word) {
  /* This func take a pointer to category_t and a word (char *), and check 
     whether the category_t already contain this word. If yes, return the 
     index (i) of the matching word; else, return -1.
  */
  for (size_t i = 0; i < source->n_words; i++) {
    if (strcmp((source->words)[i], word) == 0) {
      return i;
    }
  }
  // if not found
  return -1;
}

void deleteWord(char * category, catarray_t * cats, const char * word) {
  /* This func delete the given word of the given category in 'catarray_t * cats'
   */
  char * wordCopy = malloc((strlen(word) + 1) * sizeof(*wordCopy));
  strcpy(wordCopy, word);

  // free and set the current 'char * word' to NULL
  int indexCat = lookupCategory(cats, category);
  category_t * targetCat = &(cats->arr[indexCat]);
  int indexWord = lookupWord(targetCat, wordCopy);
  free(targetCat->words[indexWord]);
  targetCat->words[indexWord] = NULL;

  // free the wordCopy we malloced in the beginning of the func
  free(wordCopy);

  // COND 1 -  if the category contains only this 1 word, delete the old 'char ** words'
  size_t oldWordsSz = targetCat->n_words;
  if (oldWordsSz == 1) {
    free(targetCat->words);
    targetCat->words = NULL;
    targetCat->n_words = 0;
    return;
  }

  // COND 2 - the category containes more than this 1 word
  // malloc a new 'char ** words'
  char ** new = malloc((oldWordsSz - 1) * sizeof(*new));
  // copy everything from old to the new 'char ** words'
  size_t j = 0;
  for (size_t i = 0; i < oldWordsSz; i++) {
    if (targetCat->words[i] != NULL) {
      new[j] = targetCat->words[i];
      j++;
    }
  }
  // free the old 'char ** words'
  free(targetCat->words);
  // move the pointer to point to the new 'char ** words'
  targetCat->words = new;
  // update the size of the new 'char ** words'
  targetCat->n_words--;
}

void replaceNPrint(char ** lines, size_t sz, catarray_t * cats, int option) {
  /* This func prints each string in lines, while replacing each '_category_' 
     with the respected word.

     Inputs:
     char ** lines - the array of strings to print
     size_t sz - the size of 'lines'
     catarray_t * cats - a pointer to the struct where to search category/words
     option - =1 if option '-n' is passed in, else =0

     Output: void
  */

  // declare a category_t to store usedWords
  category_t used;
  used.name = "used";
  used.n_words = 0;
  used.words = NULL;

  //start parsing each line in the story template
  for (size_t i = 0; i < sz; i++) {
    char * str = lines[i];

    // STEP 1 - if str contains _category_
    char * underscore = strchr(str, '_');
    while (underscore != NULL) {  // found _category_

      // 1a. print the part before '_category_'
      while (str < underscore) {
        fprintf(stdout, "%c", *str);
        str++;
      }
      str++;  // now the string starts right after the 1st '_'

      // 1b. check error in '_category_'
      underscore = strchr(str, '_');
      if (underscore == NULL) {
        fprintf(stderr,
                "Error: Wrong format of '_category' found in inputFile(story)!\n");
        exit(EXIT_FAILURE);
      }
      else if (str == underscore) {
        fprintf(stderr, "Error: Wrong format of '__' found in inputFile(story)!\n");
        exit(EXIT_FAILURE);
      }

      // 1c. copy the 'category' into a seperate string
      char * category = copyPartialString(&str, underscore, 1);

      // 1d. replace _category_ with the corresponding word + print it to stdout
      // ---------------- For Story-step1----------------------------
      if (cats == NULL) {
        const char * word = chooseWord(category, cats);
        fprintf(stdout, "%s", word);
      }
      // ---------------- For story-step3 & 4----------------------------
      else {
        // CONDITION A - _category_ is a category (not a pos integer)
        if (checkPosInt(category) != 1) {
          const char * word = chooseWord(category, cats);
          fprintf(stdout, "%s", word);
          storeWord(&used, word);  // add the word to the list of used words
          if (option == 1) {
            deleteWord(category, cats, word);
          }
        }
        else {  // CONDITION B - category is a positive integer (>=0)
          size_t a = atoi(category);  // size_t???
          const char * word = findPreviousWord(&used, a);
          fprintf(stdout, "%s", word);
          storeWord(&used, word);
        }
      }

      // 1e. free char * category
      free(category);

      // 1f. check if the rest of str still contains _category_
      underscore = strchr(str, '_');
    }  // the end of loop - while('_category_' can be found in str){}

    // STEP 2 - when no more '_category_' is found in str
    fprintf(stdout, "%s", str);
  }  // the end of for loop (parsing each line of the story template)

  // STEP 3 -  free 'char ** words' in 'category_t used'
  if (used.words != NULL) {
    freeLines(used.words, used.n_words);
  }
}

catarray_t * parsingWC(char ** lines, size_t sz) {
  /* This func parses the input 'char ** lines' into sets of a category and words in this category,
     and store the sets into a catarray_t.

     Input :
     char ** lines -  an array of lines (to parse), which are in format of 'category:word\n\0'
     size_t sz - the size of char ** lines
     
     Output:
     catarray_t * - a pointer to the data structure where the sets of category and words are stored
   */

  catarray_t * ans = malloc(sizeof(*ans));
  ans->arr = NULL;
  ans->n = 0;

  for (size_t i = 0; i < sz; i++) {
    char * str = lines[i];

    // 1. check errors
    char * colon = strchr(str, ':');
    if (colon == NULL) {
      fprintf(stderr, "Error: No ':' found in 'categoryword' in inputFile(words)!\n");
      exit(EXIT_FAILURE);
    }

    // 2. parsing the line into category and word
    char * category = copyPartialString(&str, colon, 1);
    char * newLine = strchr(str, '\n');
    char * word = copyPartialString(&str, newLine, 1);

    // 3. store category and word
    int index;
    if ((index = lookupCategory(ans, category)) ==
        -1) {  // if this category doesn't exit yet
      // malloc a new category_t for this category in the array
      ans->arr = realloc(ans->arr, (ans->n + 1) * sizeof(*(ans->arr)));
      category_t * currCatp = &ans->arr[ans->n];
      ans->n++;

      // intialize the new category_t (i.e. store the category and word)
      // 3a. store category
      currCatp->name = malloc((strlen(category) + 1) * sizeof(*(currCatp->name)));
      strcpy(currCatp->name, category);
      // 3b. store word
      currCatp->words = NULL;
      currCatp->n_words = 0;
      storeWord(currCatp, word);
    }
    else {  // if this category already exit
      if (lookupWord(&(ans->arr[index]), word) == -1) {
        // if this word doesn't exist yet, store the word
        category_t * currCatp = &ans->arr[index];
        storeWord(currCatp, word);
      }
      // if this word already exist in this category, do nothing
    }
    free(category);
    free(word);
  }
  return ans;
}

void freeCatarray_t(catarray_t * cats) {
  /* This func frees all the memory allocated by the input -- catarray_t * cat */

  // for each category in the array
  for (size_t i = 0; i < cats->n; i++) {
    category_t * currCatp = &cats->arr[i];
    // for each word in the category_t
    for (size_t j = 0; j < currCatp->n_words; j++) {
      free(currCatp->words[j]);
    }
    free(currCatp->words);
    free(currCatp->name);
  }
  free(cats->arr);
  free(cats);
}
