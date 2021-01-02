#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x);

int main()
{
  double x,a,b,c;

  a = 11;
  b = 15;
  c = 20;

  while(fabs(a-c) > 1E-6)
    {
      if(fabs(b-a) > fabs(c-b))
	{
	  x = (a+b)/2;
	  if(f(x) > f(b)) //then the interval is (x,b,c)
	    {
	      b = x;
	      printf("%lf\n",x);
	    }
	  else //the interval is (a,x,b)
	    {
	      c = b;
	      b = x;
	      printf("%lf\n",x);
	    }
	}
      else
	{
	  x = (b+c)/2;
	  if(f(x) > f(b)) //then the interval is (a,b,x)
	    {
	      c = x;
	      printf("%lf\n",x);
	    }
	  else //the interval ix (b,x,c)
	    {
	      a = b;
	      b = x;
	      printf("%lf\n",x);
	    }
	}
    }
  printf("The root is: x = %lf, f(x) = %lf\n",x,f(x));
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
