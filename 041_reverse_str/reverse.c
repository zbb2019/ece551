#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  //WRITE ME!

  // find the 1st "\0" in the string, and assign a pointer to it
  char * nullTerminatorPtr = strchr(str, '\0');
  // if the first char of string is "\0", then it's an empty string
  if (nullTerminatorPtr == str) {
    return;
  }
  // assign pointers to the first and the last char in the string
  char * first = str;
  char * last = nullTerminatorPtr - 1;
  // exchange chars in first and last until we reach the middle
  while (first < last) {
    char temp = *first;
    *first = *last;
    *last = temp;
    // increment first and last to the next set of exchange
    first++;
    last--;
  }
  // finish switching, return
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be "
                "no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
