/* Exercise 2.6:  Iterative method to find pi */

#include <stdio.h>
#include <math.h>

int main()
{
  double x0,y0,x1,y1,pi0,pi1;
  int i;

  x0 = sqrt(2.0);
  x1 = (1.0 + x0)/(2.0*sqrt(x0));
  y1 = sqrt(sqrt(2.0));
  x0 = x1;

  /* Note that the iteration begins with y1, not with y0 */

  y0 = y1;
  pi0 = 2 + sqrt(2);
  pi1 = pi0*(x1+1.0)/(y1+1.0);
  pi0 = pi1;
  printf("x(1) = %f  y(1) = %f pi(1) = %17.15f\n",x1,y1,pi1);

  for(i=2;i<=10;i++) {
    x1 = (1.0 + x0)/(2.0*sqrt(x0));
    y1 = (1.0 + x0*y0)/((1.0+y0)*sqrt(x0));
    pi1 = pi0*(x1+1.0)/(y1+1.0);
    printf("x(%d) = %f  y(%d) = %f pi(%d) = %17.15f\n",i,x1,i,y1,i,pi1);
    x0 = x1;
    y0 = y1;
    pi0 = pi1;
  } 

  return(0);
}
