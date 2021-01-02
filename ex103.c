#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "comphys.h"
#include "comphys.c"

int main() {
  FILE *in,*out,*rsp;
  float *y, *wave;
  int j, m, M, N;
  float sum, sum1, xmax;

  sum = 0.0;
  sum1 = 0.0;

  m = 1;
  M = 65536; //y must be a power of 2

  y = vector(1,M);
  wave = vector(1,M);
  
  // Prepare to write for plotting
  printf("\nLow pass filter -- Fast Fourier transform algorithm (outfile = \"ex103.out\")\n\n");
  if ((in=fopen("UHA21.nor","r"))==NULL) {
    printf("\nCannot open file for output\n");
    return(0);  		
  }

  if ((out=fopen("ex103.out","w"))==NULL) {
    printf("\nCannot open file for output\n");
    return(0);  		
  }

 
  while (fscanf(in,"%f %f", &wave[m], &y[m]) != EOF) m++; //read in file until no more data, then input zeros for the rest:
  while(m<=M) { //zero pad the rest of the terms
    wave[m] = wave[m-1];
    y[m] = 0.0;
    m++;
  }

  for(j=1;j<=m;j++) sum += y[j];

  realft(y, M, 1); //(data to transform, size of array (1..n), ???)

  /* CHANGE THIS: Values of N will select 
what frequencies to filter **(low-pass) */
  N = 10000; 
  
  xmax = wave[N]; //(for GNUplot)
  while(N<=M) { //zero-out past N (the user-input frequency selector)
    y[N] = 0.0;
    N++;
  }  
  
  for(j=1;j<=M;j++) sum1 += y[j];
  for(j=1;j<=M;j++) y[j] *= sum/sum1;

  realft(y, M, -1); //(data to transform, size of array (1..n), ???)


  for(m=1;m<=M;m++){
    fprintf(out,"%f %f\n",wave[m],y[m]);
  }
  
  

  if((rsp = fopen("gnuplot.rsp","w")) == NULL) {
    printf("\nCannot open gnuplot.rsp for writing\n"); exit(1);
  }
  fprintf(rsp,"set xrange [3823.0 : %f]\n",xmax);
  fprintf(rsp,"plot '%s' using 1:2 with lines\n","ex103.out");
  fprintf(rsp,"pause mouse\n");
  fprintf(rsp,"replot\n");
  fclose(rsp);
  if(system("gnuplot gnuplot.rsp") == -1) {
    printf("\nCommand could not be executed\n");
    exit(1);
  }
  fclose(in);
  fclose(out);
  
  return(0);
}
