#include "pandemic.h"

#include <stdio.h>
#include <string.h>

country_t parseLine(char * line) {
  /* Step 1
     Input:
     1. a string (char * line) in the following format: 
     "country's name, 12345", where 12345 is the population number     
     
     Return:
     1. country_t ans (a struct which has array country_t.name 
     and int country_t.population)
     
     Do:
     Store the country's name and population number from the 
     input string into country_t ans (which we will return afterwards)  
     */

  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;

  //MY ANSWER BELOW
  //1. check input error 1
  if (line == NULL) {
    fprintf(stderr,
            "Error in the input file, processing stopped:\n"
            "\tchar * line points to NULL:\n"
            "\t%s\n",
            line);
    exit(EXIT_FAILURE);
  }
  char * lineCopy = line;

  //2. check input error 2
  // CITE the next line -  man strchr - char *strchr(const char *s, int c);
  char * comma = strchr(line, ',');
  if (comma == NULL) {
    fprintf(stderr,
            "Error in the input file, processing stopped:\n"
            "\tNo comma detected in this input line:\n"
            "\t%s\n",
            line);
    exit(EXIT_FAILURE);
  }

  //3. filling country_t.name[]
  int i = 0;
  while (lineCopy < comma) {
    ans.name[i] = *lineCopy;
    lineCopy++;
    i++;
  }
  ans.name[i] = '\0';

  //4. filling country_t.population
  lineCopy = comma + 1;
  while (*lineCopy == ' ') {
    lineCopy++;
  }

  // check input error 3
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

  // CITE the next line - man strtol - long int strtol(const char *nptr, char **endptr, int base);
  ans.population = strtol(lineCopy, NULL, 10);

  //5. return country_t
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  /* Step 2
     Input:
     1. unsigned* data - an array of daily case data
     2. size_t n_days - the number of days over which data is measured
     3. double * avg - where to write the result of the calculation

     Return: void
     
     Do: Calculates the 7-day running average of daily case data
     */

  // check input errors
  if (n_days < 7 || data == NULL) {
    fprintf(stderr, "Error: data is empty or less than 7-day\n");
    exit(EXIT_FAILURE);
  }

  // calculate the result
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
  /* Step 3
     Input:
     1. unsigned* data - an array of daily case data
     2. size_t n_days - the number of days over which data is measured
     3. uint64_t pop - the population for that country
     4. double * cum - where to write the result of the calculation

     Return: void
     
     Do: Calculates the cumulative number of cases that day per 100,000 people.
     */

  // check input errors
  if (n_days <= 0 || data == NULL) {
    fprintf(stderr, "Error: data is empty\n");
    exit(EXIT_FAILURE);
  }

  // calculate the result
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
  /* Step 4
     Input:
     1. country_t * countries - an array of country_t's with length n_country 
     2. size_t n_countries - the length of array "countries" 
     3. unsigned* data - a 2-D array[n_countries][n_days] of daily case data, 
     with each row representing each counrtry's data of n_days
     4. size_t n_days - the number of days over which data is measured
    
     Return: void
     
     Do: 
     Finds the maximum number of daily cases of all countries repsented in the data,
     for any day over the entire time period. Then print the name of that country and
     the max number of daily cases. If there's a tie, then print a message for tie.  
     */

  // check input errors
  if (n_days <= 0 || n_countries <= 0 || data == NULL) {
    fprintf(stderr, "Error: data is empty\n");
    exit(EXIT_FAILURE);
  }

  // find the maximum number (of daily cases) and that country
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

  // print the result
  if (tie == 1) {
    printf("There is a tie between at least two countries\n");
  }
  else {
    country_t maxCountry = countries[maxCountryIndex];
    printf("%s has the most daily cases with %u\n", maxCountry.name, maxNumber_cases);
  }
}
