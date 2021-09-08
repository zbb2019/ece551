#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned long expected_ans) {
  unsigned ans = power(x, y);
  if (ans != expected_ans) {
    exit(EXIT_FAILURE);
  }
}

int main() {
  // power() prototype

  run_check(0, 0, 1);
  run_check(9, 0, 1);
  run_check(0, 6, 0);
  run_check(2, 6, 64);
  run_check(254, 2, 64516);
  run_check(65000, 2, 4225000000);
  return EXIT_SUCCESS;
}
