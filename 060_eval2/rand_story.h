#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>

#include "provided.h"
//any functions you want your main to use

void replaceNPrint(char ** lines, size_t sz);
size_t readFile(FILE * f, char *** linesp);
void freeLines(char ** lines, size_t sz);

#endif
