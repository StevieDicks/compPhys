#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "comphys.h"
#include "comphys.c"

int main()
{
  float x,y,rn,r2,f,integral,V,sum,av,sum2,av2;
  int N;
  float error;
  long i;
  long idum = -1;
  time_t now;
  
  /* Use the time function to supply a different seed to the random number generator every time the program is run */
  now = time(NULL);
  idum = -1*now;

  printf("How many points of integration? N > ");
  scanf("%d",&N);
  
  /* Initialize random number generator */
  rn = ran1(&idum);
  
  /* Our region V that encloses W, a circle of unit radius, is a square with sides of length 2. Thus, the area of this square is 4 */
  V = 2 * 3.141592654;
  sum = 0.0;
  sum2 = 0.0;
  
  for(i=0;i<N;i++)
    {


      /* Following gives x between -1.0 and 1.0, and y between -pi/2 and +pi/2 */
      x = 2.0*ran1(&idum) - 1.0;
      y = 3.141592654*ran1(&idum) - 3.141592654/2;
      r2 = x*x * cos(y);

      /* Is the point in the region W? */
      //if(r2 <= 1.0) f = r2;
      //else f = 0.0;
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
  printf("\nIntegral = %f +/- %f\n",integral,error);
  return(0);
}
