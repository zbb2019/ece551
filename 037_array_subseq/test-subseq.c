#include <stdio.h>
#include <stdlib.h>

// prototype maxSeq()
size_t maxSeq(int * array, size_t n);

void run_check(int * array, size_t n, size_t expected_ans) {
  size_t ans = maxSeq(array, n);
  if (ans != expected_ans) {
    // print error warnings
    printf("Test failed!\n");
    printf("Array: {");
    for (int i = 0; i < n - 1; i++) {
      printf("%d, ", array[i]);
    }
    printf("%d}, input size: %zu\n", array[n - 1], n);
    printf("Expected: %zu, Actual: %zu\n", expected_ans, ans);

    // Exit_Failure
    exit(EXIT_FAILURE);
  }
}

int main() {
  int a[] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  int b[] = {5, 8, 1, 67, 99, -3, -2, -1, 0, 1};

  run_check(a, 10, 4);
  run_check(a, 4, 2);
  run_check(b, 10, 5);
  run_check(b, 0, 0);
  run_check(b, 20, 5);

  printf("All test cases passed!!! :)\n");
  return EXIT_SUCCESS;
}
