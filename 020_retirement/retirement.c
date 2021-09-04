#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double calculation(retire_info x, int startAge, double initial_balance) {
  int age_in_months = startAge;
  double balance = initial_balance;
  for (int i = 0; i < x.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n",
           age_in_months / 12,
           age_in_months % 12,
           balance);
    balance += (x.contribution + balance * x.rate_of_return);
    age_in_months++;
  }
  return balance;
}

void retirement(int startAge,         //in months
                double initial,       //initial savings in dollars
                retire_info working,  //info about working
                retire_info retired)  //info about being retired
{
  // computer your retirement account balance each month while your are working
  double balance_after = calculation(working, startAge, initial);
  int age_after_working = startAge + working.months;

  // computer your retirement account balance each month while your are retired
  balance_after = calculation(retired, age_after_working, balance_after);
}

int main() {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;  //per month

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;  //per month

  int startAge = 327;
  double initial = 21345;

  retirement(startAge, initial, working, retired);
  return EXIT_SUCCESS;
}
