#include "rand_story.h"

#include <stdio.h>
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

void checkFileExist(FILE * f) {
  /* This func check whether the file we opened exists or not. */
  if (f == NULL) {
    fprintf(stderr, "Usage: Input file doesn't exist!\n");
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

void replaceNPrint(char ** lines, size_t sz) {
  /* This func prints each string in lines, while replacing each '_category_' 
     with the respected word.

     Inputs:
     char ** lines - the array of strings to print
     size_t sz - the size of 'lines'

     Output: void
  */

  for (size_t i = 0; i < sz; i++) {
    char * str = lines[i];

    // 1. check if this sentense contains _category_
    char * underscore = strchr(str, '_');
    while (underscore != NULL) {  // found _category_

      // 2a. print the part before '_'
      while (str < underscore) {
        fprintf(stdout, "%c", *str);
        str++;
      }
      str++;  // now the string starts right after the 1st '_'

      // 2b. check error for _category_
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

      // 2c. copy category into a seperate string
      char * category = copyPartialString(&str, underscore, 1);

      // 2d. call chooseWord() and print the returned word
      const char * word = chooseWord(category, NULL);
      fprintf(stdout, "%s", word);

      // free char * category
      free(category);

      // 2e: Next Loop Iteration:
      // continue to check if the rest of the sentence contains _category_
      underscore = strchr(str, '_');
    }

    //3. print the part after all '_category_' (no _category_ found in str)
    fprintf(stdout, "%s", str);
  }
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
      currCatp->words = malloc(sizeof(*(currCatp->words)));
      currCatp->words[0] = malloc((strlen(word) + 1) * sizeof(*(currCatp->words[0])));
      strcpy(currCatp->words[0], word);
      currCatp->n_words = 1;
    }
    else {  // if this category already exit
      if (lookupWord(&(ans->arr[index]), word) == -1) {
        // if this word doesn't exist yet, store the word
        category_t * currCatp = &ans->arr[index];
        currCatp->words = realloc(currCatp->words,
                                  (currCatp->n_words + 1) * sizeof(*(currCatp->words)));
        currCatp->words[currCatp->n_words] =
            malloc((strlen(word) + 1) * sizeof(*(currCatp->words[currCatp->n_words])));

        strcpy(currCatp->words[currCatp->n_words], word);
        currCatp->n_words++;
      }
      // if this word already exist in this category, do nothing
    }
    free(category);
    free(word);
  }
  return ans;
}

void freeCatarray_t(catarray_t * cat) {
  /* This func frees all the memory allocated by the input -- catarray_t * cat */

  // for each category in the array
  for (size_t i = 0; i < cat->n; i++) {
    category_t * currCatp = &cat->arr[i];
    // for each word in the category_t
    for (size_t j = 0; j < currCatp->n_words; j++) {
      free(currCatp->words[j]);
    }
    free(currCatp->words);
    free(currCatp->name);
  }
  free(cat->arr);
  free(cat);
}
