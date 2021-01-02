/* Key for Exercise 3.7.  Convert CO2 values in vostok_co2.dat into
differential temperatures (relative to today), print to output file, then
display results with Gnuplot */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
  double co2,dT;
  int year;
  FILE *in,*out,*rsp;

  if((in = fopen("vostok_co2.dat","r")) == NULL) {
    printf("Cannot open vostok data file\n");
    exit(1);
  }
  if((out = fopen("vostok_co2.out","w")) == NULL) {
    printf("Cannot open vostok data file\n");
    exit(1);
  }

  // Read in data & convert to differential temperature
  while(fscanf(in,"%d %lf",&year,&co2) != EOF) {
    dT = 2.5*(co2-365.0)/280.0;
    fprintf(out,"%d %4.2f\n",year,dT);
  }
  fclose(in);
  fclose(out);

  // Plot results using gnuplot
  if((rsp = fopen("gnuplot.rsp","w")) == NULL) {
    printf("\nCannot open gnuplot.rsp for writing\n");
    exit(1);
  }
  fprintf(rsp,"plot 'vostok_co2.out' using 1:2 with lines\n");
  fprintf(rsp,"pause mouse\n");
  fprintf(rsp,"replot\n");
  fclose(rsp);
  if(system("gnuplot gnuplot.rsp") == -1) {
    printf("\nCommand could not be executed\n");
    exit(1);
  }

  return(0);
} 
