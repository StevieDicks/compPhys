/* READ DATA IN */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "comphys.h"
#include "comphys.c"

float *t,*yi;
int k;
float f(float x[]);

const double pi = 3.141592653589793;

int main()
{
  float *p,**xi,fret;
  int iter=0;
  int i,j;
  float A1,P1,A2,P2;
  FILE *in;

  p = vector(1,4);
  t = vector(0,300);
  yi = vector(0,300);
  
  
  if((in = fopen("SIM.dat","r")) == NULL) {
    printf("\nCannot find input file\n");
    exit(1);
  }

  /* initiate yi[] */
  k = 0;
  while(fscanf(in,"%f %f",&t[k],&yi[k]) != EOF ) k++;

  fclose(in);
  
  /* Allocate memory for the p vector and the xi matrix */
  xi = matrix(1,4,1,4);
  
  /* initial point */
  A1 = 7.0;
  P1 = 12.0;
  A2 = 1.0;
  P2 = 1.0;
  
  p[1] = A1;
  p[2] = P1;
  p[3] = A2;
  p[4] = P2;
  
  /* Initial directions */
  for(i=1;i<=4;i++) {
    for(j=1;j<=4;j++) {
      if(i == j) xi[i][j] = 1.0;
      else xi[i][j] = 0.0;
    }
  }

  /* invoke powell with ftol = 0.001 */
  powell(p,xi,4,0.001,&iter,&fret,f);
  printf("\nThe minimum is found at A1 = %f, P1 = %f, A2 = %f, P2 = %f.",p[1],p[2],p[3],p[4]);
  printf("\nThe value of f at the minimum is %f\n",fret);
  return(0);
}

/*
x[1] = A1
x[2] = P1
x[3] = A2
x[4] = P2
 */

float f(float x[])
{
  double y1,chi2;
  int i;


  chi2 = 0.0;
  for(i=0;i<k;i++) {
    y1 = x[1]*sin(2*pi*t[i]/x[2]) + x[3]*sin(2*pi*t[i]/x[4]);
    chi2 += (y1 - yi[i])*(y1 - yi[i]);
  }
  printf("\nchi2 = %f",chi2);
  return(chi2);
}
