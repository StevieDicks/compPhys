/* Convolution problem: sun.dat (wavelength, intensity) */

#include <stdio.h>
#include <stdlib.h>
#include "comphys.c"
#include "comphys.h"



int main() {
  unsigned long m, n, M;
  float *data, *respns, *ans, *l1;
  float dl, l, li, lf;
  float h1, r1;
  int i,j;
  FILE *in, *out, *rsp;

  double FWHM = 0.2;
  double o = FWHM/2.355;

  n = 512;
  m = 512;
  dl = 0.005;
  M = 16384;

  y = vector(1,M);

  data = vector(1,M);
  respns = vector(1,m);
  ans = vector(1,2*n);

  in = fopen("sun.dat","r");
  
  /* Define h(l) */
  l = -2.56;
  i=1;
  while(fscanf(in,"%f %f\n",&l1[i],&data[i]) != EOF) i++; //read in file until no more data, then input zeros for the rest:
  while(i<=M) { //zero pad the rest of the terms
    data[i] = 0.0;
    y[i] = y[i-1];
    i++;
  }

  /* Define response function -- note wrapping of negative part to
     second half of vector */
  l = 0.0;
  for(i=1;i<=256;i++) {
    respns[i] = exp((-l*l)/(2*o));
    l += dl;
  }
  for(i=257;i<=512;i++) respns[i] = 0.0;

  for(j=1;j<=m;j++) sum += y[j];
  
  convlv(data,128,respns,128,1,ans);

  for(j=1;j<=M;j++) sum1 += y[j];
  for(j=1;j<=M;j++) y[j] *= sum/sum1;

  if((rsp = fopen("gnuplot.rsp","w")) == NULL) {
    printf("\nCannot open gnuplot.rsp for writing\n"); exit(1);
  }
  //fprintf(rsp,"set xrange [3823.0 : %f]\n",);
  fprintf(rsp,"plot '%s' using 1:2 with lines\n","sun.dat");
  fprintf(rsp,"pause mouse\n");
  fprintf(rsp,"replot\n");
  fclose(rsp);
  if(system("gnuplot gnuplot.rsp") == -1) {
    printf("\nCommand could not be executed\n");
    exit(1);
  }
  fclose(in);
  fclose(out);

  free_vector(data,1,256);
  free_vector(respns,1,256);
  free_vector(ans,1,512);
  free_vector(l1,1,512);
  return(0);
}
