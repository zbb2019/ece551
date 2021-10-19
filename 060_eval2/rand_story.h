#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>

#include "provided.h"
//any functions you want your main to use

void checkArgc(int argc, int expectArgc);
void checkFileExist(FILE * f);
void replaceNPrint(char ** lines, size_t sz);
size_t readFile(FILE * f, char *** linesp);
void freeLines(char ** lines, size_t sz);

int lookupCategory(catarray_t * source, char * category);
int lookupWord(category_t * source, char * word);
char * copyPartialString(char ** start, char * end, int nullTerminatorYN);
catarray_t * parsingWC(char ** lines, size_t sz);
void freeCatarray_t(catarray_t * cat);

#endif
