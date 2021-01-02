/* Problem 3 Exam 3.  Linear least squares fit to resonant optical scattering
   data using the method of the vector of functions */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "comphys.h"
#include "comphys.c"
double pi = 3.141592653589793;
float X1(float x);
float X2(float x);
float X3(float x);
float X4(float x);
float X5(float x);

int main()
{
  float(*X[5])(float) = {X1,X2,X3,X4,X5};  //The vector of functions
  FILE *in;
  int i,j,k,l,N;
  float *x,*y;
  float **A,**b,*sa;
  float dev,chi2;

  //Setting up the matrices and vectors for the problem
  A = matrix(1,5,1,5);
  b = matrix(1,5,1,1);
  x = vector(1,1000);
  y = vector(1,1000);
  sa = vector(1,5);

  if((in = fopen("scatter.dat","r")) == NULL) {
    printf("\nCannot open input file\n");
    exit(1);
  }

  /* Initialize b and A with zeros */
  for(j=1;j<=5;j++) {
    b[j][1] = 0.0;
    for(k=1;k<=5;k++) A[j][k] = 0.0;
  }

  //Stuff A and b whilst reading in the data
  l = 1;
  while(fscanf(in,"%f %f",&x[l],&y[l]) != EOF) {
    for(k=1;k<=5;k++) {
      b[k][1] += y[l]*X[k-1](x[l]);
      for(j=1;j<=5;j++) A[k][j] += X[k-1](x[l])*X[j-1](x[l]);
    }
    l++;
  }
  fclose(in);

  N = l-1;

  /* Gauss-Jordan elimination.  After calling gaussj, A becomes the covariant
     matrix, and b is the solution. */
  gaussj(A,5,b,1);

  /* Calculate chi2 and errors */
  chi2 = 0.0;
  for(i=1;i<=N;i++) {
    dev = y[i];
    for(k=1;k<=5;k++) dev += -b[k][1]*X[k-1](x[i]);
    chi2 += dev*dev;
  }

  for(i=1;i<=5;i++) sa[i] = sqrt(chi2*A[i][i]/(float)(N-5));

  printf("chi2 = %e\n",chi2);

  for(k=1;k<=5;k++) printf("a[%d] = %f +/- %f\n",k,b[k][1],sa[k]);

  // Put the toys away after playing
  free_matrix(A,1,5,1,5);
  free_matrix(b,1,5,1,1);
  free_vector(x,1,1000);
  free_vector(y,1,1000);
  free_vector(sa,1,5);

  return(0);
}

float X1(float x)
{
  return(1.0);
}

float X2(float x)
{
  return(x);
}

float X3(float x)
{
  return(x*x);
}

float X4(float x)
{
  return(bessj0(2*pi*x));
}

float X5(float x)
{
  return(bessj1(pi*x));
}

