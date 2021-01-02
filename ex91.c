/* Fit data91.dat to a straight line "ax + b" */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "comphys.c"
#include "comphys.h"

float chi2i(float xi, float yi, float a, float b);
float Si();
float Sxi(float xi);
float Sxxi(float xi);
float Syi(float yi);
float Sxyi(float xi, float yi);

const float sigi = 1.0;	 

int main() {
  float *xi, *yi, a, b, D;
  float S = 0.0, Sx = 0.0, Sxx = 0.0, Sy = 0.0, Sxy = 0.0;
  FILE *in;
  int ni, i;
  float chi2 = 0.0;
  float s;
  float siga, sigb;
  float SEa, SEb;


  xi = vector(1,50);
  yi = vector(1,50);

  in = fopen("data91.dat","r");
  if((in = fopen("data91.dat","r")) == NULL) {
    printf("\nCannot open file for input\n");
    exit(1);
  }
  
  for(i=1;i<=50;i++) {
    ni = fscanf(in,"%f %f",&xi[i],&yi[i]);
  }

  for(i=1;i<=50;i++) {
    S += Si();
    Sx += Sxi(xi[i]);
    Sxx += Sxxi(xi[i]);
    Sxy += Sxyi(xi[i],yi[i]);
    Sy += Syi(yi[i]);
  }

  D = S*Sxx - Sx*Sx;

  a = (Sxx*Sy - Sx*Sxy)/D;
  b = (S*Sxy - Sx*Sy)/D;

  

  for(i=1;i<=50;i++) {
    chi2 += chi2i(xi[i],yi[i],a,b);
  }

  s = sqrt(chi2/(S-2));
  siga = sqrt(Sxx/D);
  sigb = sqrt(S/D);
  
  SEa = s*siga;
  SEb = s*sigb;

  printf("\ny = ax + b:\na = %f +/- %f, b = %f +/- %f.\nchi2 = %f.\n\n",a,SEa,b,SEb,chi2);

  fclose(in);
  return(0);
}



float chi2i(float xi, float yi, float a, float b) {
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
