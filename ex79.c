/*
  Functions employed:
  trap: carries out 1-D trapezoidal integration
  integrand: evaluates the integrand
  l1, l2: the limits
  twoDtrap: implements 2-D trapezoidal integration
  H: Carries out integration of the integrand for a given value of x
  x: to make things easy, x is declared as an external variable, so that we don’t have to pass it to each function
*/

#include <stdio.h>
#include <math.h>
double trap(double a, double b, double (*func)(double), int N);
double integrand(double y);
double l1();
double l2();
double twoDtrap(double a, double b,int N);
double H(double y1, double y2);
double x;
int N;

int main()
{
  double a = -1.0;
  double b = 1.0;
  double result;
  
  printf("\nEnter number of points for both x and y > ");
  scanf("%d",&N);
  
  result = twoDtrap(a,b,N);
  printf("\nIntegral = %e\n",result);
  
  return(0);
}



/* twoDtrap carries out trapezoidal integration on H between the limits y1 = l1(x), y2 = l2(x) and x = a and x = b */
double twoDtrap(double a, double b, int N)
{
  double h,integral;
  int i;
  h = (b-a)/(double)(N-1);
  integral = 0.0;
  x = a;
  integral += 0.5*H(l1(),l2());
  x = b;
  integral += 0.5*H(l1(),l2());
  x = a+h;
  for(i=2;i<N;i++)
    {
      integral += H(l1(),l2());
      x += h;
    }
  integral *= h;
  return(integral);
}


//////////////////////////////
double H(double y1, double y2)
{
  return(trap(y1,y2,integrand,N));
}
/* Remember that x is external, so it need not be passed to l1 and l2 */
double l1()
{
  return(-3.141592654/2);
}
///////////
double l2()
{
  return(3.141592654/2);
}
/* Only y is passed to integrand, as x is external */
double integrand(double y)
{
  return(x*x * cos(y));
}


/* Note that trap is written generally, 
so that any function (func) can be passed to it. 

Study carefully how a function is passed to another function, 
and how the passed function is referred to inside the second function. 

Note that in this case, 
only one variable can be passed to func (in this case y). */
double trap(double a, double b, double (*func)(double), int N)
{
  double h,integral,x;
  int i;
  if(a == b) return(0.0);
  
  h = (b-a)/(double)(N-1);
  integral = 0.0;
  integral += 0.5*((*func)(a) + (*func)(b));
  x = a+h;
  for(i=2;i<N;i++)
    {
      integral += (*func)(x);
      x += h;
    }
  integral *= h;
  
  return(integral);
}
