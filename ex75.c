#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "comphys.c"
#include "comphys.h"

double g(double x);

int main()
{
  int i, n;
  double a, b, x, h;
  double dx, x1, x2;
  double dy, y1, y2;
  double m, yint;
  double *f, f0 = 0, f1 = 0;

  a = 1;
  b = 2;


  /*
run integral for 30 iterations
   */
  n = 30;
  f = dvector(1,n);
  x = a;
  for(i=1;i<=n;i++)
    {
      h = (b-a)/(n-1);
      if(i==1||i==n)
	{
	  f[i] = .5 * g(x);
	  x += h;
	}
      else
	{
	  f[i] = g(x);
	  x += h;
	}
      f0 += f[i];
    }
  f0 = h*f0;
  printf("y1 (N = 30) = %lf\n",f0);
  x1 = (n*n);
  x1 = 1/x1;
  y1 = f0;

  
  /*
run integral for 80 iterations
   */
  n = 80;
  f = dvector(1,n);
  x = a;
  for(i=1;i<=n;i++)
    {
      h = (b-a)/(n-1);
      if(i==1||i==n)
	{
	  f[i] = .5 * g(x);
	  x += h;
	}
      else
	{
	  f[i] = g(x);
	  x += h;
	}
      f1 += f[i];
    }
  f1 = h*f1;
  printf("y2 (N = 80) = %lf\n",f1);
  x2 = (n*n);
  x2 = 1/x2;
  y2 = f1;


  /*
find the slope between the two points... then find the y intercept "yint" to find value for N = infinite. 
   */
  dy = y2 - y1;
  dx = x2 - x1;
  m = dy/dx;

  //printf("x1 = %le, x2 = %le, dy = %le, dx = %le, m = %le\n",x1,x2,dy,dx,m);
  printf("calculate y-intercept using:\n     y2 = m*x2 + b :: (%1.3e) = (%1.3e)*(%1.3e) + b.\n",y2,m,x2);
  
  //y2 = m*x2 + yint... so:
  yint = y2 - m*x2;

  printf("     b = %lf.\n",yint);

  printf("\n Deviation from \"exact\" value, 1.440422:\n N = 30: dy1 = %e,\n N = 80: dy2 = %e,\n N = \"infinite\": db = %e.\n",fabs(1.440422-y1),fabs(1.440422-y2),fabs(1.440422-b));
  
  return(0);
}

double g(double x)
{
  double f;
  f = x * sin(x);
  return (f);
}
