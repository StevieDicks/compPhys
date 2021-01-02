/* 4-point Lagrangian interpolation of BK7 data */

#include <stdio.h>
#include <math.h>
#include "comphys.c"
#include "comphys.h"

double interp(double wave);

int main(){
  int ni;
  double x,index;

  printf("\nPlease enter value for wavelength of light. This program will return the refractive index for BK7 Glass for a specific wavelength between 3511 and 23254 Angstroms\n>");
  ni = scanf("%lf",&x);

  while(3511 > x || 23254 < x){
    printf("\nPlease enter another value\n>");
    ni = scanf("%lf",&x);
  }

  index = interp(x);
  printf("\nThe index of refraction is %1.5f.\n",index); 
 
  //free_vector(xn,0,34);
  //free_vector(yn,0,34);
  return(0);
}

double interp(double x){
  double L = 0.0;
  int i;
  int j = 0;
  //int n;
  double x1,x2,x3,x4;
  double y1,y2,y3,y4;
  double term1,term2,term3,term4;
  

  double xn[35]={3511.0,3638.0,4047.0,4358.0,4416.0,4579.0,4658.0,4727.0,4765.0,4800.0,4861.0,4880.0,4965.0,5017.0,5145.0,5320.0,5461.0,5876.0,5893.0,6328.0,6438.0,6563.0,6943.0,7860.0,8210.0,8300.0,8521.0,9040.0,10140.0,10600.0,13000.0,15000.0,15500.0,19701.0,23254.0};
  double yn[35]={1.53894,1.53648,1.53024,1.52669,1.52611,1.52462,1.52395,1.52339,1.52310,1.52283,1.52238,1.52224,1.52165,1.52130,1.52049,1.51947,1.51872,1.51680,1.51673,1.51509,1.51472,1.51432,1.51322,1.51106,1.51037,1.50981,1.50894,1.50731,1.50669,1.50371,1.50130,1.50068,1.49500,1.48929};

  for(i=0;i<35;i++){
    if(xn[i] < x && xn[i+1] >= x){
      j=i;
      break;
    }
  }

  //L = yn[j-1]*((x-xn[j])*(x-xn[j+1])*(x-xn[j+2]))/((xn[j-1]-xn[j])*(xn[j-1]-xn[j+1])*(xn[j-1]-xn[j+2])) + yn[j]*((x-xn[j-1])*(x-xn[j+1])*(x-xn[j+2]))/((xn[j]-xn[j-1])*(xn[j]-xn[j+1])*(xn[j]-xn[j+2])) + yn[j+1]*((x-xn[j-1])*(x-xn[j])*(x-xn[j+2]))/((xn[j+1]-xn[j-1])*(xn[j+1]-xn[j])*(xn[j+1]-xn[j+2])) + yn[j+2]*((x-xn[j-1])*(x-xn[j])*(x-xn[j+1]))/((xn[j+2]-xn[j-1])*(xn[j+2]-xn[j])*(xn[j+2]-xn[j+1]));
  //^^^^#HASHTAG #THE #HARD #WAY^^^^
  //Easy method below:

  
  x1 = xn[j-1];
  x2 = xn[j];
  x3 = xn[j+1];
  x4 = xn[j+2];

  y1 = yn[j-1];
  y2 = yn[j];
  y3 = yn[j+1];
  y4 = yn[j+2];

  term1 = y1*((x-x2)*(x-x3)*(x-x4))/((x1-x2)*(x1-x3)*(x1-x4));
  term2 = y2*((x-x1)*(x-x3)*(x-x4))/((x2-x1)*(x2-x3)*(x2-x4));
  term3 = y3*((x-x1)*(x-x2)*(x-x4))/((x3-x1)*(x3-x2)*(x3-x4));
  term4 = y4*((x-x1)*(x-x2)*(x-x3))/((x4-x1)*(x4-x2)*(x4-x3));
  
  if(j==0){
    j = j+1;
  }else if(j==34){
    j = j-1;
  }

  L = term1 + term2 + term3 + term4;
    

  //free_vector(xn,0,34);
  //free_vector(yn,0,34);
  return(L);
}
