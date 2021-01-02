/* Ex 9.5  R.O. Gray */
#include <stdio.h>
#include <math.h>
#include "comphys.h"
#include "comphys.c"

/* Fits a sine series n = 3 to data95.dat */

int main()
{
  float *x,*y;
  float x1,x2;
  float **A,**b;
  float chi2,dev,*sa;
  int m,M;
  int i,j,k,l,N;
  FILE *in;
  double pi = 3.141592653589793;

  M = 4;

  A = matrix(1,M,1,M);
  b = matrix(1,M,1,1);
  x = vector(1,120);
  y = vector(1,120);
  sa = vector(1,M);

  for(j=1;j<=M;j++) {
    b[j][1] = 0.0;
    for(k=1;k<=M;k++) A[j][k] = 0.0;
  }

  if((in = fopen("data95.dat","r")) == NULL) {
    printf("Cannot find data95.dat\n");
    exit(1);
  }

  l = 1;
  while(fscanf(in,"%f %f",&x[l],&y[l]) != EOF) {
    for(k=1;k<=M;k++) {
      if(k == 1) b[k][1] += y[l];
      else b[k][1] += y[l]*sin((k-1)*pi*x[l]);
      for(j=1;j<=M;j++) {
	if(k == 1 && j == 1) A[k][j] += 1.0;
	else if(k == 1 && j != 1) A[k][j] += sin((j-1)*pi*x[l]);
	else if(k != 1 && j == 1) A[k][j] += sin((k-1)*pi*x[l]); 
        else A[k][j] += sin((j-1)*pi*x[l])*sin((k-1)*pi*x[l]);  
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
      else  dev += -b[k][1]*sin((k-1)*pi*x[i]);
    }
    chi2 += dev*dev;
  }

  for(k=1;k<=M;k++) sa[k] = sqrt(chi2*A[k][k]/(float)(N-M));

  printf("chi2 = %e\n",chi2);

  for(k=1;k<=M;k++) printf("a[%d] = %f +/- %f\n",k,b[k][1],sa[k]);

  free_matrix(A,1,M,1,M);
  free_matrix(b,1,M,1,1);
  free_vector(x,1,120);
  free_vector(y,1,120);
  free_vector(sa,1,M);

  return(0);
}

