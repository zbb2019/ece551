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
  // condition 1: letterForE = 'e' + key
  key = letterForE - 'e';
  if ('e' <= (123 - key)) {
    return key;
  }
  // confition 2: letterForE = ('e' - 97 + key)%26 + 97
  key = key + 26;
  if ('e' > (123 - key)) {
    return key;
  }
  return -999;
}
int test();

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
