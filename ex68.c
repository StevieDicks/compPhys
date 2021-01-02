/* 
Use planck(wave,T) (defined in comphys.c) to find maximum B(wave) at 2000k, 5000k, 8000k, 11000k, 14000k. Use GNUplot against 1/T to show that the slope of the line is 2.9E7 Angstrom.K. 
HINT: find Minimum of -B(wave)
 */
/*
Need to write a function to find the values of (a,b,c)!
Call this function "Wien"; Wien's law.
a = 0
b = (a+c)/2 ----midpoint of a and c
c = Wien(T) ----max wavelength for temperature
 */

#include <stdio.h>
#include <stdlib.h>
#include "comphys.c"
#include "comphys.h"
#include <math.h>

float calc(float T);
float Wien(float T);
float dplanck(float wave, float T);
  
int main()
{
  calc(2000);
  calc(5000);
  calc(8000);
  calc(11000);
  calc(14000);

  return(0);
}


float calc(float T)
{
  double x, x0, a, b, c;
  a = 0.0;    // default a = 0.0 before all loops
  c = Wien(T);
  b = (a+c)/2;
  x = b;
  x0 = 0.0;
  while(fabs(x - x0) > 1E-6)
    {
      if(dplanck(b,T) > 0)
	{
	  x0 = x;
	  x = b - (dplanck(b,T)*(c-b))/(dplanck(c,T)-dplanck(b,T));
	  a = b;
	  b = x;
	  //printf("A planck(%lf) = %lg\n",x,planck(x,T));
	}
      else if(dplanck(b,T) < 0)
	{
	  x0 = x;
	  x = a - (dplanck(a,T)*(b-a))/(dplanck(b,T)-dplanck(a,T));
	  c = b;
	  b = x;
	  //printf("B planck(%lf) = %lg\n",x,planck(x,T));
	}
    }
  printf("The flux, B(%lf) = %lg\n",x,planck(x,T));

  return(0);
}

///////////////////
float Wien(float T)
{
  float f;
  f = 2.9E7 / T;
  return(f);
}


//////////////////////////////////
float dplanck(float wave, float T)
{
  float f;
  f = (1.19106E27*1.43879E8)/(T*T*(wave*wave*wave*wave*wave*wave)*(exp(1.43879E8/(wave*T))-1));
  return(f);
}
