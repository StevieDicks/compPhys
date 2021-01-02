#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "comphys.h"
#include "comphys.c"

/*
  void convlv (float data[], unsigned long n, float respns[], unsigned long m, int isign, float ans[]);

  data[] = the data set, which is +1 for t=[0,1], 0 otherwise, [1..n]
  n is number of data points, subdivision (128 here). (Must be power of 2.)
  respns[] = exp(-t/RC)
  m is number of points of response function
  isign = +1 for convolution, -1 for deconvolution
  ans[] is predefined array to store answer
*/

float h(float t);
float r(float t);
float RC = 1.0;

int main() {
  unsigned long m, n;
  float *data, *respns, *ans;
  float dt, t, ti, tf;
  float h1, r1;
  int i;
  FILE *out, *rsp;

  n = 128;
  m = 128;
  dt = 0.1;
  //t from -6.4s to 6.4s

  data = vector(1,n);
  respns = vector(1,m);
  ans = vector(1,2*n);

  ti = -6.4; //don't really use these two lines
  tf = 6.4;
  //step size:
  //dt = (tf - ti)/128 = 0.1

  t = ti;
  for (i=1; i<=128; i++) {
    data[i] = h(t);
    t += dt;
  }

  t = 0.0;
  for(i=1;i<=64;i++) {
    respns[i] = r(t);
    t += dt;
  }
  for(i=65;i<=128;i++) respns[i] = 0.0;

  //use function convlv
  convlv (data, n, respns, m, 1, ans);

  
  if((out = fopen("ex104.dat","w")) == NULL) {
    printf("\nCannot open file for output\n");
    exit(1);
  }
  
  t = ti;
  for (i=1; i<=m; i++) {
    if(t >= 0.0 && t <= 1.0) h1 = 1.0;
    else h1 = 0.0;
    if(t >= 0.0) r1 = exp(-t/(RC));
    else r1 = 0.0;
    fprintf(out,"%f %f %f %f\n",t,ans[i]/64.0,r1,h1);
    t += dt;
  }
  
  //plot Vout to Gnuplot
  if((rsp = fopen("gnuplot.rsp","w")) == NULL) {
    printf("\nCannot open gnuplot.rsp for writing\n");
    exit(1);
  }
  fprintf(rsp,"plot '%s' using 1:2 with lines\n","ex104.dat");
  fprintf(rsp,"pause mouse\n");
  fprintf(rsp,"replot\n");
  fclose(rsp);
  if(system("gnuplot gnuplot.rsp") == -1) {
    printf("\nCommand could not be executed\n");
    exit(1);
  }
  fclose(out);  

  return(0);
}

float h(float t) {
  if (t >= 0 && t < 1) return (1.0);
  else return(0.0);
}

float r(float t) {
  return(exp(-t/RC));
}


