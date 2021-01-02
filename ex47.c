/* Ex 4.7 Hydrogen Ionization */

#include <stdio.h>
#include <stdlib.h>
#include "comphys.h"
#include "comphys.c"

double interp(double N, double T);

int main(){
  double T, N;
  //double dN;
  int ni;
  double ion;

  printf("\n\nPlease enter log(N), the log of the number of electrons per centimeter,\nand T, the temperature(in kelvins):\n\n(10.0-17.0),(1000.0-15000.0)\n     log(N),T  > ");
  ni = scanf("%lf,%lf",&N,&T);
  //N is for # of electrons, T for Temp

  while(N < 10.0 || N > 17.0 || T < 1000.0 || T > 15000.0){
    printf("\nThis value is out of the range.\nPlease enter new values:\n log(N),T > ");
    scanf("%lf,%lf",&N,&T);
  }

  
  ion = interp(N,T);   //call interpolation function

  printf("\nRatio of Ionized to Total = %1.4lf\n\n",ion);
  
  return(0);
}







double interp(double N, double T){
  double y1,y2,y3,y4;
  double t;
  double u;
  int i,j,n;
  double y;
  
  double H[15][8] = {
    {0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000},
    {0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000},
    {0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000},
    {0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000},
    {0.0017,0.0002,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000},
    {0.2980,0.0407,0.0042,0.0004,0.0000,0.0000,0.0000,0.0000},
    {0.9582,0.6961,0.1864,0.0224,0.0023,0.0002,0.0000,0.0000},
    {0.9979,0.9791,0.8241,0.3191,0.0448,0.0047,0.0005,0.0000},
    {0.9998,0.9980,0.9804,0.8335,0.3335,0.0477,0.0050,0.0005},
    {1.0000,0.9997,0.9971,0.9713,0.7719,0.2529,0.0327,0.0034},
    {1.0000,0.9999,0.9994,0.9939,0.9425,0.6211,0.1408,0.0161},
    {1.0000,1.0000,0.9998,0.9984,0.9841,0.8606,0.3817,0.0581},
    {1.0000,1.0000,0.9999,0.9995,0.9948,0.9503,0.6568,0.1607},
    {1.0000,1.0000,1.0000,0.9998,0.9980,0.9807,0.8358,0.3373},
    {1.0000,1.0000,1.0000,0.9999,0.9992,0.9917,0.9229,0.5448},
  };
  double Tn[15] = {1000.0,2000.0,3000.0,4000.0,5000.0,6000.0,7000.0,8000.0,9000.0,10000.0,11000.0,12000.0,13000.0,14000.0,15000.0};
  double Ne[8] = {10.0,11.0,12.0,13.0,14.0,15.0,16.0,17.0};
  
  i=0;
  for(n=0;n<8;n++) {
    if(Ne[n] <= N && Ne[n+1] >= N) {
      i=n;
      break;
    }
  }
  
  j=0;
  for(n=0;n<15;n++) {
    if(Tn[n] <= T && Tn[n+1] >= T) {
      j=n;
      break;
    }
  }
  
  y1 = H[j][i];
  y2 = H[j][i+1];
  y3 = H[j+1][i+1];
  y4 = H[j+1][i];


  t = (N - Ne[i])/(Ne[i+1] - Ne[i]);
  u = (T - Tn[j])/(Tn[j+1] - Tn[j]);

  y = (1-t)*(1-u)*y1 + t*(1-u)*y2 + t*u*y3 + (1-t)*u*y4;
  return(y);
}
