#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double entropy(double T);

int main()
{
  double Ti, Tf, T;
  double S = 0;
  double h;
  int N = 20;
  int i;

  Ti = 298;
  Tf = 500;

  h = (Tf - Ti)/N;

  T = Ti;
  for(i=1;i<=N;i++)
    {
      if(i==1||i==N)
	{
	  S += .5 * entropy(T);
	  T += h;
	}
      else
	{
	  S += entropy(T);
	  T += h;
	}
    }
  S = h*S;

  printf("\nChange in entropy of one mole of graphite: dS = %lf (from %.0lfK to %.0lfK).\n(Calculated as an integral using %d steps.)\n\n",S,Ti,Tf,N);
  return(0);
}

double entropy(double T)
{
  double S;
  double Cp = 16.86 + 4.77E-3*T  - 8.54E5/(T*T);
  S = Cp/T;
  return(S);
}
