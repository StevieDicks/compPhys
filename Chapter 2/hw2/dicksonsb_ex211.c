#include "comphys.c"
#include "comphys.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(){
  const float eps0 = 4.5553; //for the critical epsilon value
  float S,d,eps;
  
  float x,x1,rn;      //these six lines for RNG
  long idum = -1;   //
  time_t now;       //
  now = time(NULL); //
  idum = -1*now;    //
  rn = ran1(&idum);//

  printf("\nThis program generates 100 random values for \"epsilon\"\nbetween 0.0 and 10.0 and prints the value S, \nwhich displays stochastic behavior when \nepsilon is greater than 4.5553.\n");
  printf("\n  S               epsilon    \n");
  int i;
  for(i=0;i<100;i++){
    x = ran1(&idum);
    eps = x * 10.0;
    if(eps < eps0){
      S = 7.3329 + 1.1107*eps;
    }else if(eps > eps0){
      x1 = ran1(&idum);
      if(x1 < 0.354){
	S = 12.3925 + (eps - eps0) + 0.23*(eps - eps0)*(eps - eps0);
      }
      else if(x1 >= 0.354){
	S = 12.3925 + 4.9311*(eps - eps0) - 1.02*(eps - eps0)*(eps - eps0);
      }
      printf("  %lf       %lf   \n",S,eps);
    }
  }
}
