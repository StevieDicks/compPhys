/* Solution for Exercise 2.5 -- iterative solution for the positive
   root -- note: does not work for the negative root! */

#include <stdio.h>
#include <math.h>

int main()
{
  double x1,x2;
  double e = 1.0e-6;

  // first guess at root = 1.0
  x1 = 0.0;
  x2 = 1.0;

  while(fabs(x1-x2) > e) {
    x1 = x2;
    x2 = 5.0 + 2.0/x1;
    printf("x = %f\n",x2);
  }

  return(0);
}
