/* Ex 6.4.  This program finds the temperature at which the hydrogen-line 
   strengths attain a maximum given an electron pressure, Ne */

#include <stdio.h>
#include <math.h>
double linestrength(double T);

int main()
{
  /* Very wide initial brackets, knowing that the maximum is around 10,000K */
  double a = 3000.0;
  double b = 10000.0;
  double c = 30000.0;
  double eps = 1e-6;
  double A,B,C,x;
  double fa,fb,fc,fx;

  A = a;
  B = b;
  C = c;

  fa = linestrength(a);
  fb = linestrength(b);
  fc = linestrength(c);

  while(fabs(a-c) > eps*fabs(A-C)) {
    if((b-a) >= (c-b)) {
      x = (a+b)/2.0;
      fx = linestrength(x);
      if(fx <= fb) {
	a = b;
	b = x;
	fa = fb;
	fb = fx;
      } else {
	a = x;
	fa = fx;
      }
    } else {
      x = (b+c)/2.0;
      fx = linestrength(x);
      if(fx <= fb) {
	a = b;
	b = x;
	fa = fb;
	fb = fx;
      } else {
	c = x;
	fc = fx;
      }
    }
  }

  printf("The maximum is at T = %5.0fK\n",x);
  return(0);
}

/* This is the function we are trying to maximize.  Note the negative of the
   function value is returned, as the algorithm finds a minimum */
double linestrength(double T)
{
  double gn = 8.0;
  double En = 10.2;
  double EI = 13.6;
  double h = 6.626196e-27;
  double kev = 8.617e-5;
  double k = 1.380622e-16;
  double m = 9.109558e-28;
  double Ne = 1.0e14;
  double U = 2.0;
  double pi = 3.141592654;
  double ls;

  ls = (gn*Ne*h*h*h*exp(-En/(kev*T)))/
    (2*pow(2*pi*m*k*T,1.5)*exp(-EI/(kev*T)) + Ne*h*h*h*U);

return(-ls);
}

