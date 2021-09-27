#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void frequencyCount(int * freqArray, size_t n, FILE * f) {
  if (n != 26) {
    printf("Wrong size for input: freqArray!!");
    return;
  }

  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      // use freqArray[0] for 'a', so use freqArray[c-'a'] for c
      // Note: Don't need to consider the possibility of getting Cap-case letter,
      // because encrypt.c makes its result into all lower-case
      freqArray[c - 'a'] += 1;
    }
  }
  return;
}

int maxNumInArray(int * freqArray, size_t n) {
  int currentMax = freqArray[0];
  int currentMaxIndex = 0;
  for (size_t i = 1; i < n; i++) {
    if (freqArray[i] > currentMax) {  //what if ==, what if 2 number ties?
      currentMax = freqArray[i];
      currentMaxIndex = i;
    }
  }
  return currentMaxIndex;
}

int solveEncryptionKey(int indexForE) {
  int letterForE = indexForE + 'a';
  int key;

  // Solve key:
  // Consider letterForE to be only lower-case letters ['a', 'z'],
  // because of the results from encrypt.c and the requirement for breaker.c
  key = letterForE - 'e';

  // confition 2: letterForE is between ['a'(ASCII = 97), 'd'(ASCII = 100)], key < 0
  if (key < 0) {
    key += 26;
    return key;
  }
  // condition 1: letterForE is between ['e'(ASCII = 101), 'z'(ASCII = 122)], key = [0, 26)
  else {
    return key;
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Need only inputFilename!\n");
    return EXIT_FAILURE;
  }

  // step 1
  FILE * f = fopen(argv[1], "r");

  // step 2
  int freqArray[26] = {0};
  frequencyCount(freqArray, 26, f);

  // step 3
  int indexForE = maxNumInArray(freqArray, 26);
  int key = solveEncryptionKey(indexForE);
  if ((key != -999) && (key >= 0) && (key < 26)) {
    fprintf(stdout, "%d\n", key);
    return EXIT_SUCCESS;
  }
  else {
    fprintf(stderr,
            "Failed on solving the encryption key :<\n"
            "We got (key): %d\n",
            key);
    return EXIT_FAILURE;
  }
}
