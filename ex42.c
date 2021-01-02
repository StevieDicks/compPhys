/* all interpolation should be in a function called from main, main will print the result to the screen */

/* linear interpolation of BK7 data */

#include <stdio.h>
#include <math.h>
#include "comphys.c"
#include "comphys.h"

double interp(double wave);

int main(){
  int ni;
  double x,index;

  printf("\nPlease enter value for wavelength of light. This program will return the refractive index for BK7 Glass for a specific wavelength between 3511 and 23254 Angstroms\n > ");
  ni = scanf("%lf",&x);

  while(3511 > x || 23254 < x){
    printf("\nPlease enter another value (between 3511 and 23254)\n > ");
    ni = scanf("%lf",&x);
  }

  index = interp(x);
  printf("The index of refraction is %1.5f.\n",index); 
 
  //free_vector(xn,0,34);
  //free_vector(yn,0,34);
  return(0);
}

double interp(double x){
  double y;
  int i,j,k;
  

  double xn[35]={3511.0,3638.0,4047.0,4358.0,4416.0,4579.0,4658.0,4727.0,4765.0,4800.0,4861.0,4880.0,4965.0,5017.0,5145.0,5320.0,5461.0,5876.0,5893.0,6328.0,6438.0,6563.0,6943.0,7860.0,8210.0,8300.0,8521.0,9040.0,10140.0,10600.0,13000.0,15000.0,15500.0,19701.0,23254.0};
  double yn[35]={1.53894,1.53648,1.53024,1.52669,1.52611,1.52462,1.52395,1.52339,1.52310,1.52283,1.52238,1.52224,1.52165,1.52130,1.52049,1.51947,1.51872,1.51680,1.51673,1.51509,1.51472,1.51432,1.51322,1.51106,1.51037,1.50981,1.50894,1.50731,1.50669,1.50371,1.50130,1.50068,1.49500,1.48929};

  j=0;
  k=0;
  
  for(i=1;i<35;i++){
    if(xn[i] < x && xn[i+1] >= x){
      j=i;
      break;
    }
  }

  /* for(i=1;i<35;i++){ */
  /*   if(yn[i] < y && yn[i+1] >= y){ */
  /*     k=i; */
  /*     break; */
  /*   } */
  /* } */

  y = yn[j] + ((yn[k+1] - yn[k])/(xn[j+1] - xn[j]))*(x - xn[j]);
  return(y);
}
