/* Key for Exercise 3.4.  To make things easier to understand, this
key only changes the code to incorporate the exp function.  To see
the full solution to Ex3.4 -- i.e. also using external variables --
see ex34ext.c */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double getp(int i, double x);
double geterror(double p,double pstar);
double factorial(int i);

const double pi=3.141592653589793;

int main(int argc, char *argv[])
{
  int i,N;
  int M=50; //set the maximum number of allowable steps
  double tolerance=0.0;
  double error=0.0;
  double p=0.0;
  double pstar;
  double x;

  x=pi/4.0;

  while (tolerance <= 0.0) {
    if (argc != 2) {
      printf("\nEnter the tolerance (scientific notation, e.g. 1.5e-13) > ");
      scanf("%le",&tolerance);
    } else tolerance=atof(argv[1]);
   
    if (tolerance == 0.0) {
      printf("\nTolerance can not be zero or negative, try again...\n\n");
      return(0);
    }
  }

  pstar=exp(x);

  for (i=1;i<=M;i++) {
    p=p+getp(i,x);
    error=geterror(p,pstar);
    printf("%d  %le\n",i,error);
    if (error<tolerance) {
      break;
    }
    if (i==M) {
      printf("\nThe number of iterations exceeds allowable maximum, retry\n");
      printf("\nwith new tolerance or change max limit.\n");
      break;
    }
  }
  return(0);
}

/* This function has been modified to calculate exp(x) instead of sin(x) */

double getp(int i, double x)
{
  int term0;
  double term2;

  term0 = i-1;
  term2 = pow(x,term0)/factorial(term0);
  return(term2);
}

double geterror(double p, double pstar)
{
  return ( fabs(pstar-p) );
}

double factorial(int i)
{
  int j;
  double result=1.0;

  if (i==0) {
    return(1.0);
  }
  else {
    for (j=1;j<=i;j++) {
      result=result*(double)j;
    }
  }
  return(result);
} 
