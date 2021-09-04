#include <stdio.h>
#include <stdlib.h>

#include "name.h"

int main(void) {
  printf("Hello!\n");
  printf("%s\n", getMyName());
  return EXIT_SUCCESS;
}
