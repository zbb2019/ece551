#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME

  // outFileName = inputName + ".counts"
  // add 1 below, b/c strlen() doesnt includ the terminating null character.
  char * outFileName = malloc((strlen(inputName) + 7 + 1) * sizeof(*outFileName));
  strcpy(outFileName, inputName);
  strcat(outFileName, ".counts");
  return outFileName;
}
