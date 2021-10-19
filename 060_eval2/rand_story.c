#include "rand_story.h"

#include <stdio.h>
#include <string.h>

size_t readFile(FILE * f, char *** linesp) {
  /* This func store all the lines from a file into an array of strings
     
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

  return i;
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
      int catLen = underscore - str + 1;
      char * category = malloc(catLen * sizeof(*category));
      for (int j = 0; j < (catLen - 1); j++) {
        category[j] = *str;
        str++;
      }
      category[catLen - 1] = '\0';
      str++;  // now the string starts right after the 2nd '_'

      // 2c. call chooseWord() and print the returned word
      const char * word = chooseWord(category, NULL);
      fprintf(stdout, "%s", word);

      // free char * category
      free(category);

      // 2d: Next Loop Iteration:
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
