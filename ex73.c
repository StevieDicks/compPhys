#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "comphys.c"
#include "comphys.h"

double g(double x);

int main()
{
  int n, i;
  double a, b, x, h;
  double *f, f0 = 0;

  a = 1;
  b = 2;
  n = 19;

  x = a;

  h = (b-a)/(n-1);

  f = dvector(1,n);

  i = 1;
  while(i<=n)
    {
      if(i==1 || i==n)
	{
	  f[i] = (h/3)*g(x);
	}
      else if((i % 2) == 1)
	{
	  f[i] = 2*(h/3)*g(x);
	}
      else
	{
	  f[i] = 4*(h/3)*g(x);
	}
      f0 += f[i];
      x = x + h;
      i++;
    }

  printf("%lf\n",f0);
  return(0);
}

double g(double x)
{
  double f;
  f = x * sin(x);
  return (f);
}
