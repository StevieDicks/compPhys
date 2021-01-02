#include <math.h>
#include <stdio.h>
#include "comphys.h"
#include "comphys.c"

float *t,*yi;
int k;
float f(float x[]);
const float pi = 3.141592654;

int main(){
  float a1, a2, a3, a4;
  float x, y;
  float *p,**xi,fret;
  int iter=0;
  int i,j;
  FILE *in;

  p = vector(1,4);
  t = vector(0,200);
  yi = vector(0,200);

  if((in = fopen("data95.dat","r")) == NULL) {
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
  a1 = 0.1;
  a2 = 0.5;
  a3 = 0.2;
  a4 = 0.1;
  
  p[1] = a1;
  p[2] = a2;
  p[3] = a3;
  p[4] = a4;
  
  /* Initial directions */
  for(i=1;i<=4;i++) {
    for(j=1;j<=4;j++) {
      if(i == j) xi[i][j] = 1.0;
      else xi[i][j] = 0.0;
    }
  }

  /* invoke powell with ftol = 0.001 */
  powell(p,xi,4,0.001,&iter,&fret,f);
  printf("\nThe minimum is found at a1 = %f, a2 = %f, a3 = %f, a4 = %f.",p[1],p[2],p[3],p[4]);
  printf("\nThe value of f at the minimum is %f\n",fret);
  return(0);
}

float f(float x[]){
  float y, chi2;
  int i;

  chi2 = 0.0;
  for(i=0;i<k;i++){
    y = x[1] + x[2]*sin(pi*t[i]) + x[3]*sin(2*pi*t[i]) + x[4]*sin(3*pi*t[i]);
    chi2 += (y - yi[i])*(y - yi[i]);
  }
  printf("\nchi2 = %f",chi2);
  return(chi2);
}
