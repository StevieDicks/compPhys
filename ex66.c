/* Ex 6.6: do ex 6.2 using derivative information */
/* 
Ex 6.2 says to solve LaPlace's equation using Legendre polynomials... Write a C-program to find the //minimum// of the n=3 polynomial:
                      P3(x) = 1/2 (5x^3 - 3x) 
using the initial bracket (0.0, 0.5, 1.0).
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double P3(double x);
double dP3(double x);

int main()
{
  double x0 = 0.0,x = 0.5,a,b,c;

  a = 0.0;
  b = 0.5;
  c = 1.0;

  while(fabs(x - x0) > 1E-6)
    {
      if(dP3(b) > 0)
	{
	  x0 = x;
	  x = b - (dP3(b)*(c-b))/(dP3(c)-dP3(b));
	  a = b;
	  b = x;
	  printf("P3(%lf) = %lf\n",x,P3(x));
	}
      else if(dP3(b) < 0)
	{
	  x0 = x;
	  x = a - (dP3(a)*(b-a))/(dP3(b)-dP3(a));
	  c = b;
	  b = x;
	  printf("P3(%lf) = %lf\n",x,P3(x));
	}
    }
  printf("The minimum of P3 is P3(%lf) = %lf\n",x,P3(x));
  
  return(0);  
}

double P3(double x)
{
  double f;
  f = .5*x*(5*x*x - 3);
  return(f);
}

double dP3(double x)
{
  double f;
  f = .5*(15*x*x - 3);
  return(f);
}
