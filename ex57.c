//T from 100K to 600K; Find T when nu = 20.1 uPa.s
//Bisection problem
//Using Newton Raphson method, solve with an initial guess of T = 200K

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double nu(double x);
int sgn(double y);
double nuPrime(double x);

/////////////////////////////////////////////////////////
int main()
{
  double nu0 = 20.1;
  //double a = 100, b = 600;  //stick to these values, though (min T and max T)
  double x1, x0 = 200;
  //int sgnmid,sgna,sgnb;
  double eps = 1E-6;

  x1 = x0 - nu(x0)/nuPrime(x0);

  /*
If the derivative is negative and the function is above the desired point, need to go to the right.
If the derivative is negative and the function is below the desired point, need to go to the left. 
If the derivative is positive and the function is below the desired point, need to go to the right.
If the derivative is positive and the function is above the desired point, need to go to the left.

I think all of this [^^^^^^] is accounted for in the Newton-Raphson formula.
  */
  

  while(fabs(x0-x1) > eps*500)
    {
      
      x0 = x1;
      x1 = x1 - (nu(x1)-nu0)/nuPrime(x1);
      /*It is nu(x1) - nu0 b/c it is not accounting 
for the fact that nu0 is not centered around zero--
it is centered around 20.1 (for this example).
Subtracting nu0 centers it around zero.
      */
    }
  
  printf("\nThe Temperature when the viscocity of air,\nnu = 20.1uPa*s (in Kelvins): %lf.\n\n",x1);

  return(0);
}

/////////////////////////////////////////////////////////
double nu(double x)
{  
  double nu;
  
  nu = 3.61111E-8*x*x*x - 6.95238E-5*x*x + 0.0805437*x - 0.3;
  
  return(nu);
}


/////////////////////////////////////////////////////////
double nuPrime(double x)
{
  double nuPrime;

  nuPrime = 1.08333E-7*x*x - 0.000139048*x + 0.0805437;

  return(nuPrime);
}
