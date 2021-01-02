/* The full key for Exericise 3.4.  See ex34.c for a simpler version.  This
   version passes all variables as external variables */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double getp();
double geterror();
double factorial();
int I;
double x;
double p=0.0;
double pstar;
int term0;

const double pi=3.141592653589793;

int main(int argc, char *argv[])
{
  int i,N;
  int M=50; //set the maximum number of allowable steps
  double tolerance=0.0;
  double error=0.0;

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
    I = i;
    p=p+getp();
    error=geterror();
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

double getp()
{
  double term2;
  int i;

  i = I;
  term0 = i-1;
  term2 = pow(x,term0)/factorial();
  return(term2);
}

double geterror()
{
  return ( fabs(pstar-p) );
}

double factorial()
{
  int i,j;
  double result=1.0;

  i = term0;
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
