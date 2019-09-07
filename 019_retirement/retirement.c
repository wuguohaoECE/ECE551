#include<stdlib.h>
#include<stdio.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

struct _info{
  int age;
  double initial;
};

typedef struct _info info;
typedef struct _retire_info retire_info;



info account_change(int startAge,double initial, retire_info info1){
  for(int i=0;i<info1.months;i++){
     int age = startAge/12;
     int months = startAge%12;
     printf("Age %3d month %2d you have $%.2lf\n",age,months,initial);
     initial+=initial*info1.rate_of_return+info1.contribution;
     startAge++;
   };
   info result;
   result.age=startAge;
   result.initial=initial;
   return result;
}


void retirement(int startAge, double initial, retire_info working, retire_info retired){
  info account=account_change(startAge,initial,working);
  account=account_change(account.age,account.initial,retired);
  }

int main(void){
  retire_info working;
  working.months=489;
  working.contribution=1000;
  working.rate_of_return=0.045/12;
  retire_info retire;
  retire.months=384;
  retire.contribution=-4000;
  retire.rate_of_return=0.01/12;
  retirement(327,21345,working,retire);
  return 0;
}
    
