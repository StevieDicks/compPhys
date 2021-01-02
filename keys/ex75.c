/* Ex 7.5 R.O. Gray: Using the trapezoidal rule to obtain an "exact" answer */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double integrand(double x);
double trap(double a, double b, double (*func)(double), int N);

int main()
{
  double a = 1.0;
  double b = 2.0;
  double x[2],y[2],m,B;
  double true = 1.440422;
  double error;
  int N[2] = {30,80};
  int i;

  for(i=0;i<2;i++) {
    x[i] = 1.0/(double)(N[i]*N[i]);
    y[i] = trap(a,b,integrand,N[i]);
    error = true - y[i];
    printf("%e %f %f\n",x[i],y[i],error);
  }

  m = (y[1]-y[0])/(x[1]-x[0]);
  B = y[0] - m*x[0];
  error = true - B;

  printf("\nThe integral is %f with error %f\n",B,error);

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

double integrand(double x)
{
  return(x*sin(x));
}
