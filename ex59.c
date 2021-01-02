#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "comphys.c"
#include "comphys.h"

//float bessj1(float x)

int main()
{
  double x1, x0;
  double eps = 1E-6;

  x1 = 2;
  x0 = 0;
  while(fabs(x0 - x1) > eps)
    {
      x0 = x1;
      x1 = x1 + bessj0(x1)/bessj1(x1);
    }
  printf("First Bessel0 root: %lf\n",x1);

  x1 = 5;
  x0 = 0;
  while(fabs(x0 - x1) > eps)
    {
      x0 = x1;
      x1 = x1 + bessj0(x1)/bessj1(x1);
    }
  printf("Second Bessel0 root: %lf\n",x1);

  return(0);
}
