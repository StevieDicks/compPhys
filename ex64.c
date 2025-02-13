/* Hydrogen Balmer Lines */
/////SEE KEY ex64.c FOR ACTUAL PROGRAM
/////DID NOT ACCOUNT FOR CHANGE IN ALL FUNCTIONS 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double BLS(double T);

int main()
{
  double x,a,b,c;

  a = 2500;
  b = 2650;
  c = 2800;

  while(fabs(a-c) > 1E-7)
    {
      if(fabs(b-a) >= fabs(c-b))
  	{
  	  x = (a+b)/2;
  	  if(BLS(x) > BLS(b)) //(a, x, b)
  	    {
	      c = b;
	      b = x;
  	      //b = x;
  	      printf("%lg, %5.6lf\n",BLS(x),x);
  	    }
  	  else //(x, b, c)
  	    {
	      a = x;
  	      //c = b;
  	      //b = x;
  	      printf("%lg, %5.6lf\n",BLS(x),x);
  	    }
  	}
      else
  	{
  	  x = (b+c)/2;
  	  if(BLS(x) > BLS(b)) //(b,x,c)
  	    {
	      a = b;
	      b = x;
  	      //c = x;
  	      printf("%lg, %5.6lf\n",BLS(x),x);
  	    }
  	  else //(a,b,x)
  	    {
	      c = x;
  	      //a = b;
  	      //b = x;
  	      printf("%lg, %5.6lf\n",BLS(x),x);
  	    }
  	}
    }
  printf("The root is: T = %lf K, Line Strength (T) =  %lg\n",x,BLS(x));
  return(0);
}

//Balmer Line Series
double BLS(double T) 
{
  double f;
  double gn = 8;
  double En = 10.2;
  double E1 = 13.6;
  const double h = 6.626196E-27;
  const double kev = 8.617E-5;
  const double k = 1.380622E-16;
  const double m = 9.109558E-28;
  const double pi = 3.14159265359;
  double U = 2.00;
  double Ne = 1E14;

  f = (gn*Ne*h*h*h*exp(-En/(kev*T)))/(2*pow(2*pi*m*k*T , 3/2)*exp(-E1/(kev *T)) + Ne*h*h*h*U);

  return(f);
}
