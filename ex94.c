#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float X1(float x);
float X2(float x);
float X3(float x);
float X4(float x);
const float pi = 3.141592654;
float chi2i(float xi, float yi, float a, float b);
float Si();
float Sxi(float xi);
float Sxxi(float xi);
float Syi(float yi);
float Sxyi(float xi, float yi);
const float sigi = 1.0;	 

int main() {
  FILE *in;
  int M, N;
  double s;
  int ni;
  double *ak;
  int i;
  double y;

  if((in = fopen("data94.dat","r")) == NULL) {
    printf("\nCannot find input file\n");
    exit(1);
  }

  printf("What degree polynomial should the program fit the data?\nM = ");
  ni = scanf("%d",&M);

  ak = dvector(1,M); //might need to change to (0,M-1);

  /* Write a summation program to get y = sum[ ak * Xk ], from k = 1 to M */
  for(i=0;i<M;i++) {
    y += pow(x,i); //this will take the sum of 1, x, x^2, x^3, ..., x^(M-1)
  }
  
  for(i=1;i<=50;i++) {
    S += Si();
    Sx += Sxi(x[i]);
    Sxx += Sxxi(x[i]);
    Sxy += Sxyi(x[i],y[i]);
    Sy += Syi(y[i]);
  }

  D = S*Sxx - Sx*Sx;

  a1 = (Sxx*Sy - Sx*Sxy)/D;
  b1 = (S*Sxy - Sx*Sy)/D;

  for(i=1;i<=101;i++) {
    chi2 += chi2i(x[i],y[i],a1,b1);
  }

  s = sqrt(chi2/(S-2));
  siga = sqrt(Sxx/D);
  sigb = sqrt(S/D);
  
  SEa = s*siga;
  SEb = s*sigb;

  errA[1] = a[1][1]*chi2/(l-4);
  errA[2] = a[2][1]*chi2/(l-4);
  errA[3] = a[3][1]*chi2/(l-4);
  errA[4] = a[4][1]*chi2/(l-4);

  printf("\ny = ax + b:\na = %f +/- %f, b = %f +/- %f.\nchi2 = %f.\n\n",a1,SEa,b1,SEb,chi2);
  
  printf("\na = {\n");
  for(i=1;i<=4;i++) {
    printf("{ %f +/- %f },\n", a[i][1],errA[i]);
  }
  printf("}\n\n");

  return(0);
}

double chi2i(double){
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
  return(x*x*x);
}

float X5(float x) {
  return(x*x*x*x);
}
