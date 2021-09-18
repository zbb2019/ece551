#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }

  size_t maxCount = 1;
  size_t count = 1;
  int currentNumber = array[0];
  for (size_t i = 1; i < n; i++) {
    if (array[i] > currentNumber) {
      count += 1;
    }
    else {
      if (count > maxCount) {
        maxCount = count;
      }
      count = 1;
    }
    currentNumber = array[i];
  }
  if (count > maxCount) {
    maxCount = count;
  }
  return maxCount;
}
