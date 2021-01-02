/* Ex 9.4  R.O. Gray */
#include <stdio.h>
#include <math.h>
#include "comphys.h"
#include "comphys.c"

/* Fits a polynomial of degree M to data94.dat */

int main()
{
  float *x,*y;
  float **A,**b;
  float chi2,dev,*sa;
  int m,M;
  int i,j,k,l,N,ni;
  FILE *in;

  printf("\nInput degree of polynomial > ");
  ni = scanf("%d",&m);

  M = m+1;

  A = matrix(1,M,1,M);
  b = matrix(1,M,1,1);
  x = vector(1,60);
  y = vector(1,60);
  sa = vector(1,M);

  for(j=1;j<=M;j++) {
    b[j][1] = 0.0;
    for(k=1;k<=M;k++) A[j][k] = 0.0;
  }

  if((in = fopen("data94.dat","r")) == NULL) {
    printf("Cannot find data94.dat\n");
    exit(1);
  }

  l = 1;
  while(fscanf(in,"%f %f",&x[l],&y[l]) != EOF) {
    for(k=1;k<=M;k++) {
      b[k][1] += y[l]*pow(x[l],(double)(k-1));
      for(j=1;j<=M;j++) 
	A[k][j] += pow(x[l],(double)(j-1))*pow(x[l],(double)(k-1));  
    }
    l++;
  }

  N = l-1;

  gaussj(A,M,b,1);

  chi2 = 0.0;
  for(i=1;i<=N;i++) {
    dev = y[i];
    for(k=1;k<=M;k++) dev += -b[k][1]*pow(x[i],(double)(k-1));
    chi2 += dev*dev;
  }

  for(k=1;k<=M;k++) sa[k] = sqrt(chi2*A[k][k]/(float)(N-M));

  printf("chi2 = %e\n",chi2);
  for(k=1;k<=M;k++) printf("a[%d] = %f +/- %f\n",k,b[k][1],
                    sa[k]);

  free_matrix(A,1,M,1,M);
  free_matrix(b,1,M,1,1);
  free_vector(x,1,60);
  free_vector(y,1,60);
  free_vector(sa,1,M);

  return(0);
}


