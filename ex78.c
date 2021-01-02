/*redo 7.2 with Gauss-Legendre integration*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "comphys.c"
#include "comphys.h"

double ti(double a, double b, double xi);
double g(double T);

int main()
{
  int n;
  double a, b, x;
  double *f, *t, f0 = 0;

  a = 298;
  b = 500;
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

  printf("\nChange in entropy of one mole of graphite: dS = %lf (from %.0lfK to %.0lfK).\n\n",f0,a,b);
  return(0);
}

double g(double T)
{
  double S;
  double Cp = 16.86 + 4.77E-3*T  - 8.54E5/(T*T);
  S = Cp/T;
  return(S);
}

double ti(double a, double b, double xi)
{
  double f;
  f = (a + b)/2 + (b - a)*xi/2;
  return(f);
}
