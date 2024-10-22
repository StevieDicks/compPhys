/* Ex 9.5  R.O. Gray */
#include <stdio.h>
#include <math.h>
#include "comphys.h"
#include "comphys.c"

/* Fits a sine series n = 3 to data95.dat */

float X0(float t);
float X1(float t);
float X2(float t);
float X3(float t);
float X4(float t);
double pi = 3.141592653589793;

int main()
{
  float *x,*y;
  float x1,x2;
  float **A,**b;
  float chi2,dev,*sa;
  int m,M;
  int i,j,k,l,N;
  FILE *in;
  float (*X[5])(float) = {X0,X1,X2,X3,X4};


  M = 5;

  A = matrix(1,M,1,M);
  b = matrix(1,M,1,1);
  x = vector(1,700);
  y = vector(1,700);
  sa = vector(1,M);

  for(j=1;j<=M;j++) {
    b[j][1] = 0.0;
    for(k=1;k<=M;k++) A[j][k] = 0.0;
  }

  if((in = fopen("co2.dat","r")) == NULL) {
    printf("Cannot find co2.dat\n");
    exit(1);
  }

  l = 1;
  while(fscanf(in,"%f %f",&x[l],&y[l]) != EOF) {
    for(k=1;k<=M;k++) {
      if(k == 1) b[k][1] += y[l];
      else b[k][1] += y[l]*X[k](x[l]);
      for(j=1;j<=M;j++) {
	if(k == 1 && j == 1) A[k][j] += 1.0;
	else if(k == 1 && j != 1) A[k][j] = X[j](x[l]);
	else if(k != 1 && j == 1) A[k][j] = X[k](x[l]); 
        else A[k][j] = X[j](x[l])*X[k](x[l]);  
      }
    }
    l++;
  }

  N = l-1;

  gaussj(A,M,b,1);

  chi2 = 0.0;
  for(i=1;i<=N;i++) {
    dev = y[i];
    for(k=1;k<=M;k++) {
      if(k == 1) dev += -b[k][1];
      else  dev += -b[k][1]*X[k](x[i]);
    }
    chi2 += dev*dev;
  }

  for(k=1;k<=M;k++) sa[k] = sqrt(chi2*A[k][k]/(float)(N-M));

  printf("chi2 = %e\n",chi2);

  for(k=1;k<=M;k++) printf("a[%d] = %f +/- %f\n",k,b[k][1],sa[k]);

  free_matrix(A,1,M,1,M);
  free_matrix(b,1,M,1,1);
  free_vector(x,1,700);
  free_vector(y,1,700);
  free_vector(sa,1,M);

  return(0);
}

float X0(float t) {
  return(1);
}

float X1(float t) {
  return(t);
}

float X2(float t) {
  return(t*t);
}

float X3(float t) {
  return(cos(2*pi*t));
}

float X4(float t) {
  return(t*cos(2*pi*t));
}
