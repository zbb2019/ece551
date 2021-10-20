#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>

#include "provided.h"
//any functions you want your main to use

void checkArgc(int argc, int expectArgc);
void checkFileExist(FILE * f, char * filename);
size_t readFile(FILE * f, char *** linesp);
char * copyPartialString(char ** start, char * end, int nullTerminatorYN);
void storeWord(category_t * cat, const char * word);
int checkPosInt(char * category);
const char * findPreviousWord(category_t * usedp, size_t index);
void freeLines(char ** lines, size_t sz);

int lookupCategory(catarray_t * source, char * category);
int lookupWord(category_t * source, char * word);
void deleteWord(char * category, catarray_t * cats, const char * word);

void replaceNPrint(char ** lines, size_t sz, catarray_t * cats, int option);
catarray_t * parsingWC(char ** lines, size_t sz);

void freeCatarray_t(catarray_t * cat);

#endif
