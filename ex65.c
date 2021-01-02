#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x);
double df(double x);
int main()
{
  double x0 = 0,x = 1,a,b,c;

  a = 11;
  b = 15;
  c = 20;

  while(fabs(x - x0) > 1E-6)
    {
      if(df(b) > 0)
	{
	  x0 = x;
	  x = b - (df(b)*(c-b))/(df(c)-df(b));
	  a = b;
	  b = x;
	  printf("%lf\n",x);
	}
      else if(df(b) < 0)
	{
	  x0 = x;
	  x = a - (df(a)*(b-a))/(df(b)-df(a));
	  c = b;
	  b = x;
	  printf("%lf\n",x);
	}
    }
  printf("The root at %lf = %lf\n",x,f(x));
  
  return(0);     
}

double f(double x)
{
  double f;
  f = 15 + x*(6 + x*(-24 + x));
  //Multiplication is CPU intensive;
  //This function reduces 5 multiplications to merely two.
  //i.e. this is 2.5 times as fast--
  //this IS significant with more complex programs!
  //Original: f = x*x*x - 24*x*x + 6*x + 15;
  
  return(f);
}

double df(double x)
{
  double df;
  df = 6 + x*(-48 + 3*x);

  return(df);
}
