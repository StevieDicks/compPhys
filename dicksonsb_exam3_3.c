#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "comphys.c"
#include "comphys.h"

float *x, *y;
float X1(float x);
float X2(float x);
float X3(float x);
float X4(float x);
float X5(float x);
const float pi = 3.141592654;
float chi2i(float xi, float yi, float a, float b);
float Si();
float Sxi(float xi);
float Sxxi(float xi);
float Syi(float yi);
float Sxyi(float xi, float yi);
const float sigi = 1.0;

int main() {
  float **a, **A, **b;
  float *errA;
  float (*X[5])(float) = {X1,X2,X3,X4,X5};
  /* Note that X[2](5.0) will call function X3 and pass 5.0 to it */

  float S = 0.0, Sx = 0.0, Sxx = 0.0, Sy = 0.0, Sxy = 0.0;
  float chi2 = 0.0;
  float s, D, a1, b1;
  float siga, sigb;
  float SEa, SEb;
  int i,j,k,l,M,m,N;
  FILE *in;

  m = 1;
  M = 5; //coefficients a1 through a5
  N = 5;

  errA = vector(1,5);
  x = vector(1,1001);
  y = vector(1,1001);
  a = matrix(1,5,1,1);
  A = matrix(1,5,1,5);
  b = matrix(1,5,1,1);

  for(i=1;i<=5;i++)
    {
      for(j=1;j<=5;j++)
	{
	  A[i][j] = 0.0;
	}
    }

  if((in = fopen("scatter.dat","r")) == NULL) {
    printf("\nCannot find input file\n");
    exit(1);
  }

  /* initiate yi[] */
  /* This section reads in the file and creates a matrix b[M][l++] and A[M][M] */
  l = 1;
  while(fscanf(in,"%f %f",&x[l],&y[l]) != EOF )
    {
      for(k=1;k<=M;k++)
	{
	  b[k][1] += y[l]*X[k-1](x[l]);
	  for(j=1;j<=M;j++) A[k][j] += X[k-1](x[l])*X[j-1](x[l]);
	}
      l++;
    }

  fclose(in);

  gaussj(A,5,b,1); //returns inverse of A and a as b

  a[1][1] = b[1][1];
  a[2][1] = b[2][1];
  a[3][1] = b[3][1];
  a[4][1] = b[4][1];
  a[5][1] = b[5][1];

  for(i=1;i<=1001;i++) {
    S += Si();
    Sx += Sxi(x[i]);
    Sxx += Sxxi(x[i]);
    Sxy += Sxyi(x[i],y[i]);
    Sy += Syi(y[i]);
  }

  D = S*Sxx - Sx*Sx;

  a1 = (Sxx*Sy - Sx*Sxy)/D;
  b1 = (S*Sxy - Sx*Sy)/D;

  for(i=1;i<=1001;i++) {
    chi2 += chi2i(x[i],y[i],a1,b1);
  }

  s = sqrt(chi2/(S-2));
  siga = sqrt(Sxx/D);
  sigb = sqrt(S/D);
  
  SEa = s*siga;
  SEb = s*sigb;

  errA[1] = a[1][1]*chi2/(l-5);
  errA[2] = a[2][1]*chi2/(l-5);
  errA[3] = a[3][1]*chi2/(l-5);
  errA[4] = a[4][1]*chi2/(l-5);
  errA[5] = a[5][1]*chi2/(l-5);

  printf("\ny = ax + b:\na = %f +/- %f, b = %f +/- %f.\nchi2 = %f.\n\n",a1,SEa,b1,SEb,chi2);
  
  printf("\na = {\n");
  for(i=1;i<=5;i++) {
    printf("{ %f +/- %f },\n", a[i][1],errA[i]);
  }
  printf("}\n\n");

  return(0);
}

float chi2i(float xi, float yi, float a, float b){
  float sigi = 1.0;
  return(((yi - a - b*xi)/sigi)*((yi - a - b*xi)/sigi));
}

float Si(){
  return(1/(sigi*sigi));
}

float Sxi(float xi){
  return(xi/(sigi*sigi));
}
float Sxxi(float xi){
  return((xi*xi)/(sigi*sigi));
}

float Syi(float yi){
  return(yi/(sigi*sigi));
}

float Sxyi(float xi, float yi){
  return((xi*yi)/(sigi*sigi));
}

float X1(float x) {
  return(1);
}

float X2(float x) {
  return(x);
}

float X3(float x) {
  return(x*x);
}

float X4(float x) {
  return(bessj0(2*pi*x));
}

float X5(float x) {
  return(bessj1(pi*x));
}
