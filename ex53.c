//T from 100K to 600K; Find T when nu = 20.1 uPa.s
//Bisection problem

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double nu(double x);
int sgn(double y, double zeropoint);

////////////////////////////////////////////////////////////////////////////////////
int main()
{
  double nu0;
  nu0 = 20.1;                //change nu value here!
  //you can find T for other values of nu
  
  double a = 100, b = 600;  //stick to these values, though (min T and max T)
  double mid;
  int sgnmid,sgna,sgnb;
  double eps = 1E-6;
  
  mid = (b+a)/2;

  sgnmid = sgn(mid,nu0);
  sgna = sgn(a,nu0);
  sgnb = sgn(b,nu0);

  while(fabs(b-a) > eps*fabs(500.0))
    {
      if(sgnmid == sgna)
	{
	  //printf("%lf\n",mid); //print the new value of midpoint to see process
	  
	  a = mid;             //since mid is on side of a, set a = mid
	  mid = (a+b)/2;       //calculate new midpoint
	  sgnmid = sgn(mid,nu0);      //find new mid sign (pos or neg)
	  
	  //printf("%d\n",sgnmid);   //print out to see process...
	}
      else if(sgnmid == sgnb)
	{
	  //printf("%lf\n",mid);
	  
	  b = mid;
	  mid = (a+b)/2;
	  sgnmid = sgn(mid,nu0);
	  
	  //printf("%d\n",sgnmid);
	}
      else
	{
	  printf("Error\n");
	}
    }
  printf("\nThe Temperature when the viscocity of air,\nnu = 20.1uPa*s (in Kelvins): %lf.\n\n",mid);
}

////////////////////////////////////////////////////////////////////////////////////
double nu(double x)
{  
  double nu;
  
  nu = 3.61111E-8*x*x*x - 6.95238E-5*x*x + 0.0805437*x - 0.3;
  
  return(nu);
}

////////////////////////////////////////////////////////////////////////////////////
int sgn(double y, double zeropoint)
{
  if(nu(y) > zeropoint)
    {
      return(1);
    }
  else
    {
      return(-1);
    }
}
