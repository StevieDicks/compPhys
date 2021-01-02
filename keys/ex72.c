/* Ex 7.2 R.O. Gray: Uses Trapezoidal rule to integrate the heat capacity
to find the change in the entropy.  The integration is from 298K to 500K */

#include <stdio.h>
#include <math.h>
double integrand(double x);
double trap(double a, double b, double (*func)(double), int N);

int main()
{
  double a = 298.0;
  double b = 500.0;
  int N;
  double result;

  printf("\nEnter number of points > ");
  scanf("%d",&N);

  result = trap(a,b,integrand,N);

  printf("\nIntegral = %e\n",result);

  return(0);
}

/* The actual trapezoidal integration is carried out in the following
function.  Note that a function (func) is passed to this function.  This
makes this function very general, as any well-behaved function can be
integrated by this function from a to b without changing the code */

double trap(double a, double b, double (*func)(double), int N)
{
  double h,integral,x;
  int i;

  h = (b-a)/(double)(N-1);

  integral = 0.0;
  integral += 0.5*((*func)(a) + (*func)(b));
  x = a+h;
  for(i=2;i<N;i++) {
    integral += (*func)(x);
    x += h;
  }
  integral *= h;
  return(integral);
}

/* the integrand */

double integrand(double T)
{
  double a = 16.86;
  double b = 4.77e-3;
  double c = 8.54e5;

  return((a + b*T - c/(T*T))/T);
}
