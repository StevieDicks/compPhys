/* I'd really like to know a way to pass "x" or "y", as a variable, into the function "integral" so that I can avoid using the three "if" statements ("if(p==1)", etc.) 

How is this possible?
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "comphys.h"
#include "comphys.c"
#define N 1000000

float integral(float p);

int main()
{
  float X,Y,M;
  float x,y;

  M = integral(1);

  X = integral(2);
  X *= (1/M);

  Y = integral(3);
  Y *= (1/M);

  printf("\nX midpoint = %f, Y midpoint = %f\n\n",X,Y);
  
  return(0);
}

float integral(float p)
{
  float x,y,rn,r2,f,integral,V,sum,av,sum2,av2;
  float error;
  long i;
  long idum = -1;
  time_t now;
  
  /* Use the time function to supply a different seed to the random number generator every time the program is run */
  now = time(NULL);
  idum = -1*now;
  
  /* Initialize random number generator */
  rn = ran1(&idum);
  
  /* Our region V that encloses W, a circle of unit radius, is a square with sides of length 1 and 2. Thus, the area of this square is 2 */
  V = 2;
  sum = 0.0;
  sum2 = 0.0;

  if(p==1){  
    for(i=0;i<N;i++)
      {
	/* Following gives x between -1.0 and 1.0, and y between -2.0 and +2.0 */
	x = 1.0*ran1(&idum);
	y = 2.0*ran1(&idum);
	r2 = (y*sin(x*x) + 2);

	/* Is the point in the region W? */
	if(x>=0 && y>=0 && y <= (-2*x + 2)) f = r2;
	else f = 0.0;
       
	/* Evaluate sums */
	sum += f;
	sum2 += f*f;
      }
  }
  else if(p==2){  
    for(i=0;i<N;i++)
      {
	/* Following gives x between -1.0 and 1.0, and y between -2.0 and +2.0 */
	x = 1.0*ran1(&idum);
	y = 2.0*ran1(&idum);
	r2 = x*(y*sin(x*x) + 2);

	/* Is the point in the region W? */
	if(x>=0 && y>=0 && y <= (-2*x + 2)) f = r2;
	else f = 0.0;
       
	/* Evaluate sums */
	sum += f;
	sum2 += f*f;
      }
  }
  else if(p==3){  
    for(i=0;i<N;i++)
      {
	/* Following gives x between -1.0 and 1.0, and y between -2.0 and +2.0 */
	x = 1.0*ran1(&idum);
	y = 2.0*ran1(&idum);
	r2 = y*(y*sin(x*x) + 2);

	/* Is the point in the region W? */
	if(x>=0 && y>=0 && y <= (-2*x + 2)) f = r2;
	else f = 0.0;
       
	/* Evaluate sums */
	sum += f;
	sum2 += f*f;
      }
  }
  
  /* Calculate Integral and error */
  av = sum/(float)N;
  av2 = sum2/(float)N;
  integral = av*V;
  error = V*sqrt((av2-av*av)/(float)N);
  if(p==1)
    {
      printf("\nIntegral (M) = %f +/- %f\n",integral,error);
    }
  else if(p==2)
    {
      printf("\nIntegral (X) = %f +/- %f\n",integral,error);
    }
  else if(p==3)
    {
      printf("\nIntegral (Y) = %f +/- %f\n",integral,error);
    }

  return(integral);
}
