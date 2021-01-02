/* Key to problem 3, Exam 3, 2016. Fitting data in SIM.dat with the simplex
   method */
#include <stdio.h>
#include <math.h>
#include "comphys.h"
#include "comphys.c"
float *t,*yq;
int k;
float f(float x[]);

main()
{
  float **p,*y;
  int nfunk,i;
  float A1,A2,P1,P2;
  FILE *in;

  p = matrix(1,5,1,4);
  y = vector(1,5);
  t = vector(0,300);
  yq = vector(0,300);

  if((in = fopen("SIM.dat","r")) == NULL) {
    printf("\nCannot find input file\n");
    exit(1);
  }

  k = 0;
  while(fscanf(in,"%f %f",&t[k],&yq[k]) != EOF) k++;

  fclose(in);

  // Initial point
  A1 = 5.4;
  P1 = 12.5;
  A2 = 1.2;
  P2 = 1.3;

  //Setting up the simplex
  p[1][1] = A1;
  p[1][2] = P1;
  p[1][3] = A2;
  p[1][4] = P2;
  p[2][1] = A1 + 0.5;
  p[2][2] = P1;
  p[2][3] = A2;
  p[2][4] = P2;
  p[3][1] = A1;
  p[3][2] = P1 + 1.0;
  p[3][3] = A2;
  p[3][4] = P2;
  p[4][1] = A1;
  p[4][2] = P2;
  p[4][3] = A2 + 0.1;
  p[4][4] = P2;
  p[5][1] = A1;
  p[5][2] = P2;
  p[5][3] = A2;
  p[5][4] = P2+0.1;

  for(i=1;i<=5;i++) y[i] = f(p[i]);

  amoeba(p,y,4,0.001,f,&nfunk);

  A1 = (p[1][1]+p[2][1]+p[3][1]+p[4][1]+p[5][1])/5.0;
  P1 = (p[1][2]+p[2][2]+p[3][2]+p[4][2]+p[5][2])/5.0;
  A2 = (p[1][3]+p[2][3]+p[3][3]+p[4][3]+p[5][3])/5.0;
  P2 = (p[1][4]+p[2][4]+p[3][4]+p[4][4]+p[5][4])/5.0;

  printf("\nA1 = %f P1 = %f A2 = %f P2 = %f\n",A1,P1,A2,P2);

  // Deallocate
  free_matrix(p,1,5,1,4);
  free_vector(y,1,5);
  free_vector(t,0,300);
  free_vector(yi,0,300);

  return(0);
}

float f(float x[])
{
  float y1,chi2;
  float pi = 3.141592654;
  int i;


  chi2 = 0.0;
  for(i=0;i<k;i++) {
    y1 = x[1]*sin(2.0*pi*t[i]/x[2]) + x[3]*sin(2.0*pi*t[i]/x[4]);
    chi2 += (y1 - yq[i])*(y1 - yq[i]);
  }
  printf("\nchi2 = %f",chi2);
  return(chi2);
}
