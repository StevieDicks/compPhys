#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double U(double x);
double L;
double Uprime(double x);

int main()
{
  int ni;

  printf("\nThis program calculates the largest root for the General Relativity equation:\n     Ueff = -1/x + (L^2)/(2x^2) - (L^2)/(x^3).");
  printf("\nPlease enter a value for L, the reduced angular momentum\nbetween L = 4.1 and L = 5.0 > ");
  ni = scanf("%lf",&L);


  double x1, x0;
  double eps = 1E-6;

  x1 = 6;
  x0 = 0;
  while(fabs(x0 - x1) > eps)
    {
      x0 = x1;
      x1 = x1 - U(x1)/Uprime(x1);
    }
  printf("The right-most root: x = %lf\n",x1);

  return(0);
}

double U(double x)
{
  double f;
  f = -1/x + L*L/(2*x*x) - L*L/(x*x*x);
  return(f);
}

double Uprime(double x)
{
  double f;
  f = 1/(x*x) - L*L/(x*x*x) + 3*L*L/(x*x*x*x);
  return(f);
}
