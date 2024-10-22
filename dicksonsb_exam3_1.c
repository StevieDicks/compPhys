#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "comphys.h"
#include "comphys.c"

float integral(float p);
const float pi = 3.141592654;

int main() {
  float rn,r2,f,integral,V,sum,av,sum2,av2;
  float theta, phi, z, R = 1.0; //phi = asin(z/R)
  float error;
  long i;
  int k, N, ni;
  float *Ti, Tav = 0;
  float sig = 0;
  long idum = -1;
  time_t now;

  Ti = vector(1,10);
  
  /* Use the time function to supply a different seed to the random number generator every time the program is run */
  now = time(NULL);
  idum = -1*now;
  
  /* Initialize random number generator */
  rn = ran1(&idum);

  printf("\nPlease enter number of points for the Monte Carlo simulation: ");
  ni = scanf("%d",&N);
  
  /* Our region V that encloses W, a sphere of unit radius, is a square with sides of length 1 and 2. Thus, the area of this square is  */
  V = 4*pi;


  for(k=0;k<10;k++) //run this program 10 times to take an average of the 10 
    {
      sum = 0.0;
      sum2 = 0.0;
      for(i=0;i<N;i++) //take N points (user input) per integral
	{
	  /* Following gives z between -1.0 and 1.0, and phi between -pi/2 and +pi/2 */
	  z = 2.0*ran1(&idum) - 1.0;
	  phi = 2.0*pi*ran1(&idum) - pi;
	  r2 = (33.4*cos(asin(z))*(sin(phi)+1));

	  /* Is the point in the region W? */
	  f = r2;
       
	  /* Evaluate sums */
	  sum += f;
	  sum2 += f*f;
	}

  
      /* Calculate Integral and error */
      av = sum/(float)N;
      av2 = sum2/(float)N;
      integral = av*V;
      error = V*sqrt((av2-av*av)/(float)N);
      Ti[k+1] = av;
    }

  for(k=0;k<10;k++) Tav += Ti[k+1];
  Tav = Tav/10;

  for(k=0;k<10;k++) sig += (Ti[k+1] - Tav)*(Ti[k+1] - Tav);
  sig = sig/9;
  sig = sqrt(sig);
  
  printf("\nAverage Temp [C] = %f +/- %f\n",Tav,sig);

  return(0);
}
