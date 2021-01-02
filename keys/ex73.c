/* Ex 7.3 R.O. Gray: Integrates xsin(x) using Simpson's rule */

#include <stdio.h>
#include <math.h>
double integrand(double x);
double simpson(double a, double b, double (*func)(double), int N);
int iseven(int i);

int main()
{
  double a = 1.0;
  double b = 2.0;
  int N = 0;
  double result;

  /* Conditional in while loop checks to make certain N is odd */

  while(iseven(N) == 1) {
    printf("\nEnter number of points (must be odd) > ");
    scanf("%d",&N);
  }

  result = simpson(a,b,integrand,N);

  printf("\nIntegral = %e\n",result);

  return(0);
}

/* A general Simpson's rule integrator.  Note that a function (func) is
   passed to this integrator */

double simpson(double a, double b, double (*func)(double), int N)
{
  double h,x;
  double integral;
  int i;

  h = (b-a)/(double)(N-1);

  integral = 0.0;
  x = a;

  for(i=1;i<=N;i++) {
    if(i == 1 || i == N) integral += (*func)(x);
    else if(iseven(i)) integral += 4.0*(*func)(x);
    else integral += 2.0*(*func)(x);
    x += h;
  }
  integral *= h/3.0;
  return(integral);
} 

double integrand(double x)
{
  return(x*sin(x));
}

/* Checks to see if the number i is even */

int iseven(int i)
{
  if(i%2 == 0) return(1);
  else return(0);
}
