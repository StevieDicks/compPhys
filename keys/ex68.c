/* Exercise 6.8 (C) R.O. Gray.  This program uses derivative information
to determine the position of the maximum of the same Planck function */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "comphys.h"
#include "comphys.c"
float f(float x);
float fp(float x);
/* the find bracket function finds suitable brackets for the maximum for
   a given temperature */
int find_bracket(float *a, float *b, float *c);
float T[5] = {2000.0,5000.0,8000.0,11000.0,14000.0};
float t;

main()
{
  float a,b,c,x1,x2;
  float fa,fb,fc,fx;
  float fpa,fpb,fpc,fpx;
  int flag = 1;
  int i;
  FILE *out,*rsp;

  if((out = fopen("ex68.out","w")) == NULL) {
    printf("Cannot open output file\n");
    exit(1);
  }  

  for(i=0;i<5;i++) {
    a = 1000.0;
    b = 2000.0;
    c = 3000.0;
    t = T[i];
    if(find_bracket(&a,&b,&c) == 1) {
      printf("find_bracket function failed. Now exiting\n");
      exit(1);
    }

    fa = f(a);
    fb = f(b);
    fc = f(c);
    fpa = fp(a);
    fpb = fp(b);
    fpc = fp(c);
    x1 = 1.0;
    x2 = 0.0;  

    /* Note the stop condition, which helps avoid problems associated
       with machine precision */

    while(fabs((x1-x2)/(x1+x2)) > 1.0e-6) {
      x2 = x1;
      if(fp(b) <= 0 ) {
        x1 = a - (fpa*(b-a))/(fpb - fpa);
        flag = 1;
      } else {
        x1 = b - (fpb*(c-b))/(fpc - fpb);
        flag = 2;
      }
      /* The following two statements guard against overshoots */
      if(x1 >= c) x1 = (b+c)/2.0;
      if(x1 <= a) x1 = (a+b)/2.0; 
      fx = f(x1);
      fpx = fp(x1);
      if(flag == 1) {
        a = b;
        fa = fb;
        fpa = fpb;
        b = x1;
        fb = fx;
        fpb = fpx;
      }
      if(flag == 2) {
        c = b;
        fc = fb;
        fpc = fpb;
        b = x1;
        fb = fx;
        fpb = fpx;
      }
    }
    fprintf(out,"%e %f\n",1.0/T[i],b);
  }
  fclose(out);

  if((rsp = fopen("gnuplot.rsp","w")) == NULL) {
    printf("\nCannot open gnuplot response file\n");
    exit(1);
  }
  fprintf(rsp,"plot 'ex68.out' using 1:2\n");
  fprintf(rsp,"f(x) = a*x + b\n");
  fprintf(rsp,"fit f(x) 'ex68.out' using 1:2 via a,b\n");
  fprintf(rsp,"replot f(x)\n");
  fprintf(rsp,"pause mouse\n");
  fprintf(rsp,"replot\n");
  fclose(rsp);
  system("gnuplot gnuplot.rsp");

  return(0);
}

/* The Planck Function */
float f(float x)
{
  float a = 1.19106e+27;
  float b = 1.43879e+8;
  return(-a/(pow(x,5)*(exp(b/(x*t))-1.0)));
} 

/* The derivative of the Planck Function*/
float fp(float x)
{
  float a = 1.19106e+27;
  float b = 1.43879e+8;
  float q;
  q = a*(5*x*(exp(b/(x*t))-1.0)-(b/t)*exp(b/(x*t)))/
    (pow(x,7)*pow((exp(b/(x*t))-1.0),2.0));
  return(q);
}

int find_bracket(float *a, float *b, float *c)
{
  float dw = 500.0;
  float fa,fb,fc;

  while(1) {
    fa = f(*a);
    fb = f(*b);
    fc = f(*c);
    if(fb <= fc && fb <= fa) return(0);
    *a += dw;
    *b += dw;
    *c += dw;
    if(*a > 20000) return(1);
  }
}
