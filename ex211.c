/* Key for Ex 2.11.  This program simulates a stocastic function that
   bifurcates at eps = 4.5553 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "comphys.h"
#include "comphys.c"

int main()
{
  long idum = -1;
  time_t now;
  float x,rn,eps,S;
  int i;

  // Initialize random number generator
  now = time(NULL);
  idum = -1*now;
  rn = ran1(&idum);

  for(i=0;i<100;i++) {
    eps = 10.0*ran1(&idum);
    if(eps <= 4.5553) S = 7.3329 + 1.1107*eps;
    else {
      /* Simulate bifurcation */
      x = ran1(&idum);
      if(x <= 0.354) S = 12.3925 + (eps - 4.5553) + 0.23*pow(eps - 4.5553,2.0);
      else S = 12.3925 + 4.9311*(eps - 4.5553) - 1.02*pow(eps - 4.5553,2.0);
    }
    printf("%f %f\n",eps,S);
  }
  return(0);
}

