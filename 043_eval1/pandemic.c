#include "pandemic.h"

#include <stdio.h>
#include <string.h>

country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;

  //MY ANSWER BELOW
  // check input errors
  if (line == NULL) {
    printf("Error in the input file, processing stopped:\n"
           "\tchar * line points to NULL:\n"
           "\t%s\n",
           line);
    exit(EXIT_FAILURE);
  }
  char * lineCopy = line;
  //cite man strchr() - char *strchr(const char *s, int c);
  char * comma = strchr(line, ',');

  // check input errors
  if (comma == NULL) {
    printf("Error in the input file, processing stopped:\n"
           "\tNo comma detected in this input line:\n"
           "\t%s\n",
           line);
    exit(EXIT_FAILURE);
  }

  //1. filling country name[]
  int i = 0;
  while (lineCopy < comma) {
    ans.name[i] = *lineCopy;
    lineCopy++;
    i++;
  }
  ans.name[i] = '\0';

  // 2. filling population
  lineCopy = comma + 1;

  // check input errors
  while (*lineCopy == ' ') {
    lineCopy++;
  }
  char x = *lineCopy;
  if (!((x == '1') || (x == '2') || (x == '3') || (x == '4') || (x == '5') ||
        (x == '6') || (x == '7') || (x == '8') || (x == '9') || (x == '0'))) {
    printf("Error in the input file, processing stopped:\n"
           "\tThe first char detected after comma is not a number, in this input line:\n"
           "\t%s\n",
           line);
    exit(EXIT_FAILURE);
  }
  // cite man strtol() - long int strtol(const char *nptr, char **endptr, int base);
  ans.population = strtol(lineCopy, NULL, 10);
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  // check input errors
  if (n_days <= 0 || data == NULL) {
    printf("Error: data is empty\n");
    return;
  }
  double sum;
  for (size_t i = 0; i < (n_days - 6); i++) {
    sum = 0;
    for (size_t j = i; j < (i + 7); j++) {
      sum += data[j];
    }
    avg[i] = sum / 7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  // check input errors
  if (n_days <= 0 || data == NULL) {
    printf("Error: data is empty\n");
    return;
  }

  double sum = 0;
  for (size_t i = 0; i < n_days; i++) {
    sum += data[i];
    cum[i] = sum / pop * 100000;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
