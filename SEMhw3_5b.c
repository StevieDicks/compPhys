#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "comphys.h"
#include "comphys.c"

float Afunc(float x);

int main() {
  float *A, Amax, halfmax, xl, xr, x, dx, wo; //variables and constants for Amplitude of oscillation equation A = (Fo/m)*(1/sqrt(wo2-w2+4B2*w2))
  //x = w, where w is the variable frequency
  float a, b, c;
  FILE *out,*rsp;
  int i, N;

  /* The range will be ( x : (x + N*dx) ) */
  /* note: it is centered around 'wo' */
  x = 1e7; //starting frequency 
  dx = 100; //step in frequency
  N = 50000; //number of points for plot (x-axis)
  A = vector(1,N);
  wo = 12354000;

  //open data file to write
  if((out = fopen("SEMhw3_5.dat","w")) == NULL) {
    printf("\nCannot open file for output\n");
    exit(1);
  }

  //fill in the values for A(w)
  for(i=1;i<=N;i++) {
    A[i] = Afunc(x);
    x += dx;
    //printf("%g, %g\n",A[i],x);
    fprintf(out,"%g %g\n",x,A[i]);
  }

  fclose(out);

  Amax = Afunc(wo);

  /* use 'halfmax', 'xl', 'xr' to find the FWHM value */
  halfmax = .5*Amax;

  a = wo/2;    // default a = 0.0 before all loops
  c = wo;
  b = (a+c)/2;
  x = b;
  xl = 0.0;
  while(fabs(a-c) > 1E-6)
    {
      if(fabs(b-a) < fabs(c-b))
	{
	  x = (a+b)/2;
	  if(Afunc(x) > Afunc(b)) //then the interval is (x,b,c)
	    {
	      b = x;
	      printf("%lf\n",x);
	    }
	  else //the interval is (a,x,b)
	    {
	      c = b;
	      b = x;
	      printf("%lf\n",x);
	    }
	}
      else
	{
	  x = (b+c)/2;
	  if(Afunc(x) < Afunc(b)) //then the interval is (a,b,x)
	    {
	      c = x;
	      printf("%lf\n",x);
	    }
	  else //the interval ix (b,x,c)
	    {
	      a = b;
	      b = x;
	      printf("%lf\n",x);
	    }
	}
    }
  xl = x;
  printf("\nAmax = %gm\n",Amax);
  printf("xl = %f\n",xl);

  xr = wo + (wo - xl);
  printf("wo = %f\nxr = %f\n",wo,xr);

  printf("FWHM = xr - xl = %f\n",(xr-xl));

  if((rsp = fopen("gnuplot.rsp","w"))==NULL) {
    printf("\nCannot open gnuplot.rsp for writing\n");
    exit(1);
  }
  fprintf(rsp,"set logscale xy\n");
  fprintf(rsp,"set ylabel 'Amplitude (A(w)) [m]'\n");
  fprintf(rsp,"set xrange [1.0e7:1.5e7]\n");
  fprintf(rsp,"set xlabel 'Frequency (w) [Hz]'\n");
  fprintf(rsp,"set title 'Amplitude vs Frequency (log/log)'\n");
  fprintf(rsp,"set label 1 '{/=13 Amax = %em}'\nset label 1 at graph 0.20, 0.95 tc lt 3\n",Amax);
  fprintf(rsp,"set label 2 '{/=13 FWHM = %.1fm}'\nset label 2 at graph 0.30, 0.25 tc lt 3\n",(xr-xl));
  fprintf(rsp,"set label 3 '(FWHM = xr - xl = %em - %em)'\nset label 3 at graph 0.30, 0.21 tc lt 3\n",xr,xl);
  fprintf(rsp,"plot 'SEMhw3_5.dat' using 1:2 with lines\n");
  fprintf(rsp,"pause mouse\n");
  fprintf(rsp,"replot\n");
  fclose(rsp);
  if(system("gnuplot gnuplot.rsp") == -1) {
    printf("\nCommand could not be executed\n");
    exit(1);
  }

  return(0);
}

float Afunc(float x) {
  float Fo, m, wo, B; 
  Fo = 10e-12;
  m = 1.72e-15;
  wo = 12354000; //roughly the midpoint of graph
  B = 29070;

  return((Fo/m)*(1/sqrt((wo*wo - x*x)*(wo*wo - x*x) + 4*B*B*x*x)));
}
