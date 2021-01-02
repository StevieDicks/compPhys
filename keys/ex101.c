/* Ex 10.1  Plotting the first few terms of the sine series */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double pi = 3.141592654;

int main()
{
  double t = -pi;
  double dt = 0.01;
  double h;
  FILE *out,*rsp;

  out = fopen("ex101.out","w");
  if(out == NULL) {
    printf("\nCannot open output file for writing\n");
    exit(1);
  }

  while(t <= pi) {
    h = (4.0/pi)*(sin(t) + (1.0/3.0)*sin(3*t) + (1.0/5.0)*sin(5*t) + 
	     (1.0/7.0)*sin(7*t) + (1.0/9.0)*sin(9*t));
    fprintf(out,"%f %f\n",t,h);
    t += dt;
  }

  fclose(out);

  if((rsp = fopen("gnuplot.rsp","w")) == NULL) {
    printf("\nCannot open gnuplot.rsp for writing\n");
    exit(1);
  }
  fprintf(rsp,"plot 'ex101.out' using 1:2 with lines\n");
  fprintf(rsp,"pause mouse\n");
  fprintf(rsp,"replot\n");
  fclose(rsp);
  if(system("gnuplot gnuplot.rsp") == -1) {
    printf("\nCommand could not be executed\n");
    exit(1);
  }

  return(0);
}

