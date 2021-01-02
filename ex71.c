/* integrate xsin(x)dx from 1 to 2 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "comphys.c"
#include "comphys.h"

double g(double x);

int main()
{
  int n, i, ni;
  double a, b, x, h;
  double *f, f0;

  a = 1;
  b = 2;

  printf("Enter number of points for intergral. > ");
  ni = scanf("%d",&n);

  x = a;

  h = (b-a)/(n-1);

  f = dvector(1,n);

  for(i=1;i<=n;i++)
    {
      if(i==1||i==n)
	{
	  f[i] = .5*g(x);
	  x += h;
	}
      else
	{
	  f[i] = g(x);
	  x += h;
	}
      f0 = f0 + f[i];
    }

  f0 = h*f0;

  printf("%lf\n",f0);
  return(0);
}

double g(double x)
{
  double f;
  f = x * sin(x);
  return (f);
}
