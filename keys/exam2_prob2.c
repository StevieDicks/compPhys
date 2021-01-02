/* Key to problem 2, Exam 2, 2016.  Finding the root of the relativistic
   effective potential */
#include <stdio.h>
#include <math.h>
double U(double x, double L);
double Up(double x, double L); 

int main()
{
  double L,x1,x2;
  int ni,n = 0;
  double eps = 1.0e-7;
  L = 0;

  while(L < 4.1 || L > 5.0) {
    printf("Enter L_bar between 4.1 and 5.0 > ");
    ni = scanf("%lf",&L);
  }

  x1 = 10.0;
  x2 = 5.0;

  // Newton-Raphson method of finding roots
  while(fabs(x2-x1) > eps) {
    x1 = x2;
    x2 = x1 - U(x1,L)/Up(x1,L);
    n++;
    printf("Iteration %d  x = %f\n",n,x2);
  }

  printf("root = %f\n",x2);

  return(0);

}

double U(double x, double L) 
{
  return(-1.0/x + (L*L)/(2*x*x) - (L*L)/(x*x*x));
}

double Up(double x,double L)
{
  return(1.0/(x*x) - (L*L)/(x*x*x) + (3*L*L)/(x*x*x*x));
}
