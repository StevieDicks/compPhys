#include <stdio.h>
#include <math.h>
#include "comphys.h"
#include "comphys.c"

//double norm(double wave[],double flux[], double maxflux);

int main(){
  double *wave;
  double *flux;
  FILE *in,*out;
  int i,k,N;
  double result;
  double maxflux;
  double wave_of_max;
  int ni;

  N=1023;

  wave = dvector(0,1023);
  flux = dvector(0,1023);

  if((in = fopen("hip17695.flx","r")) == NULL) {
    printf("Cannot open vostok data file\n");
    exit(1);
  }
  if((out = fopen("dicksonsb_normal.dat","w")) == NULL) {
    printf("Cannot open vostok data file\n");
    exit(1);
  }

  for(i=0;i<N;i++) { //from ex39
    ni = fscanf(in,"%lf %lf",&wave[i],&flux[i]);
  }
  
  
  for(i=0;i<N;i++) {
    if(maxflux <= flux[i]) {
      maxflux = flux[i];
      wave_of_max = wave[i];
    }
  }

  printf("The max flux = %g at wavelength = %5.3lf\n",maxflux,wave_of_max);
  
  /* for(i=0;i<N;i++) { //ex38 */
  /*   result = norm(wave[i],flux[i],maxflux); */
  /*   fprintf(out,"%7.1lf  %lf\n",wave[i],result); */
  /* } */

  for(i=0;i<N;i++) { //ex38
    flux[i] = flux[i] / maxflux;
    fprintf(out,"%5.3lf  %g\n",wave[i],flux[i]);
  }

  fclose(in);
  fclose(out);

  return(0);
}


/* double norm(double wave, double flux, double maxflux){ */
/*   flux=flux/maxflux; */
/* } */
