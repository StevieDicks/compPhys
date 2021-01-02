/* Key to Problem 1, Exam 3, Fall 2016.  R.O. Gray.  The program calculates
   the mean temperature and standard deviation on the surface of a sphere */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "comphys.c"
#include "comphys.h"
float pi = 3.14159265;


int main()
{
  float theta, phi, z, rn,sum,R = 1.0;
  float T,*Tmean,Tbar,sigma;
  long idum = -1;
  time_t now;
  int i,j,N,ni;

  now = time(NULL);
  idum = -1*now;
  rn = ran1(&idum);

  printf("\nInput the number of points for the simulation > ");
  ni = scanf("%d",&N);
  Tmean = vector(1,10);

  /* This nested loop calculates the random points on the surface, determines
the temperature at each point, and then finds the mean temperature, which
is place in the vector Tmean.  10 such means are determined */
  for(j=1;j<=10;j++) {
    sum = 0.0;
    for(i=1;i<=N;i++) {
      z = 2.0*R*ran1(&idum) - R;
      theta = asin(z/R);
      phi = 2.0*pi*ran1(&idum);
      T = 33.4*cos(theta)*(sin(phi)+1.0);
      sum += T;
    }
    Tmean[j] = sum/(float)N;
  }

  /* Calculate Tbar */
  sum = 0.0;
  for(i=1;i<=10;i++) sum += Tmean[i];
  Tbar = sum/10.0;

  /* Calculate the standard deviation */
  sum = 0.0;
  for(i=1;i<=10;i++) sum += (Tmean[i]-Tbar)*(Tmean[i]-Tbar);
  sum /= 9.0;
  sigma = sqrt(sum);

  printf("Average temperature = %f +/- %f\n",Tbar,sigma);
  free_vector(Tmean,1,10);

  return(0);
}
