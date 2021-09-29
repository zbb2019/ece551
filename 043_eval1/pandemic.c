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
    fprintf(stderr,
            "Error in the input file, processing stopped:\n"
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
    fprintf(stderr,
            "Error in the input file, processing stopped:\n"
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
  if (x == '-') {
    x = *(lineCopy + 1);
  }
  if (!((x == '1') || (x == '2') || (x == '3') || (x == '4') || (x == '5') ||
        (x == '6') || (x == '7') || (x == '8') || (x == '9') || (x == '0'))) {
    fprintf(stderr,
            "Error in the input file, processing stopped:\n"
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
  if (n_days < 7 || data == NULL) {
    fprintf(stderr, "Error: data is empty\n");
    exit(EXIT_FAILURE);
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
    fprintf(stderr, "Error: data is empty\n");
    exit(EXIT_FAILURE);
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
  // check input errors
  if (n_days <= 0 || n_countries <= 0 || data == NULL) {
    fprintf(stderr, "Error: data is empty\n");
    exit(EXIT_FAILURE);
  }

  size_t maxCountryIndex = 0;
  unsigned maxNumber_cases = data[0][0];
  int tie = 0;
  for (size_t country = 0; country < n_countries; country++) {
    for (size_t day = 0; day < n_days; day++) {
      // already counted data[0][0]
      if ((country == 0) && (day == 0)) {
        continue;
      }

      // iterating over the rest of the matrix
      if (data[country][day] > maxNumber_cases) {
        maxCountryIndex = country;
        maxNumber_cases = data[country][day];
        tie = 0;
      }
      else if (data[country][day] == maxNumber_cases) {
        tie = 1;
      }
      else {  // data[country][day] < maxNumber_cases
        continue;
      }
    }
  }

  if (tie == 1) {
    printf("There is a tie between at least two countries\n");
  }
  else {
    country_t maxCountry = countries[maxCountryIndex];
    printf("%s has the most daily cases with %u\n", maxCountry.name, maxNumber_cases);
  }
}
