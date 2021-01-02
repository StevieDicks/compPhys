/* Key to problem 3, Exam 2, 2014 using Powell's method */
#include <stdio.h>
#include <math.h>
#include "comphys.h"
#include "comphys.c"
float *t,*yq;
int k;
float f(float x[]);

main()
{
  float *p,**xi,fret;
  int nfunk,i,iter=0,j;
  float A1,A2,P1,P2;
  FILE *in;

  p = vector(1,4);
  xi = matrix(1,4,1,4);
  t = vector(0,300);
  yq = vector(0,300);

  if((in = fopen("SIM.dat","r")) == NULL) {
    printf("\nCannot find input file\n");
    exit(1);
  }

  k = 0;
  while(fscanf(in,"%f %f",&t[k],&yq[k]) != EOF) k++;

  fclose(in);

  // The initial point
  A1 = 5.4;
  P1 = 12.5;
  A2 = 1.2;
  P2 = 1.3;
 
  // Setting up the basis vectors
  for(i=1;i<=4;i++) {
    for(j=1;j<=4;j++) {
      if(i ==j) xi[i][j] = 1.0;
      else xi[i][j] = 0.0;
    }
  }

  p[1] = A1;
  p[2] = A2;
  p[3] = P1;
  p[4] = P2;

  powell(p,xi,4,0.001,&iter,&fret,f);

  printf("\nA1 = %f, P1 = %f, A2 = %f P2 = %f\n",p[1],p[3],p[2],p[4]);

  free_vector(p,1,4);
  free_matrix(xi,1,4,1,4);
  free_vector(t,0,300);
  free_vector(yq,0,300);

  return(0);
}

float f(float x[])
{
  float y1,chi2;
  float pi = 3.141592654;
  int i;


  chi2 = 0.0;
  for(i=0;i<k;i++) {
    y1 = x[1]*sin(2.0*pi*t[i]/x[3]) + x[2]*sin(2.0*pi*t[i]/x[4]);
    chi2 += (y1 - yq[i])*(y1 - yq[i]);
  }
  printf("\nchi2 = %f",chi2);
  return(chi2);
}
