/* integrate xsin(x)dx from 1 to 2 with Gauss-Legendre */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "comphys.c"
#include "comphys.h"

double ti(double a, double b, double xi);
double g(double x);

int main()
{
  int n;
  double a, b, x;
  double *f, *t, f0 = 0;

  a = 1;
  b = 2;
  n = 5;

  x = a;

  t = dvector(1,5);
  f = dvector(1,n);
  t[1] = ti(a,b,-0.90618);
  t[2] = ti(a,b,-0.538469);
  t[3] = ti(a,b,0);
  t[4] = ti(a,b,0.538469);
  t[5] = ti(a,b,0.90618);


  f0 = 0.568889*g(t[3]) + 0.478629*(g(t[2])+g(t[4])) + 0.236927*(g(t[1])+g(t[5]));
  f0 = ((b - a)/2) * f0;

  printf("%lf\n",f0);
  return(0);
}

double g(double x)
{
  double f;
  f = x * sin(x);
  return (f);
}

double ti(double a, double b, double xi)
{
  double f;
  f = (a + b)/2 + (b - a)*xi/2;
  return(f);
}
