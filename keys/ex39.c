/* Key for Exercise 3.9.  Convert CO2 values in vostok_co2.dat into
differential temperatures (relative to today), print to output file, then
display results with Gnuplot */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "comphys.h"
#include "comphys.c"

int main()
{
  double *co2,dT,dum2,maxco2,minco2;
  int *year,N,dum1,i,year_of_max,year_of_min,ni;
  FILE *in,*out,*rsp;

  if((in = fopen("vostok_co2.dat","r")) == NULL) {
    printf("Cannot open vostok data file\n");
    exit(1);
  }

  // Read in data into dummy variables and count
  N = 0;
  while(fscanf(in,"%d %lf",&dum1,&dum2) != EOF) N++;
  fclose(in);

  // Allocate space for vectors
  year = ivector(0,N-1);
  co2 = dvector(0,N-1);

  // Reopen data file to set pointer back at beginning
  if((in = fopen("vostok_co2.dat","r")) == NULL) {
    printf("Cannot open vostok data file\n");
    exit(1);
  }

  // Read the data into vectors
  for(i=0;i<N;i++) {
    ni = fscanf(in,"%d %lf",&year[i],&co2[i]);
  }
  fclose(in);

  // Find min and max
  maxco2 = -10.0;
  minco2 = 500.0;
  for(i=0;i<N;i++) {
    if(maxco2 <= co2[i]) {
      maxco2 = co2[i];
      year_of_max = year[i];
    }
    if(minco2 >= co2[i]) {
      minco2 = co2[i];
      year_of_min = year[i];
    }
  }

  printf("The minimum value of co2 (%5.1f ppm) occured in year %d\n",minco2,
	 year_of_min);
  printf("The maximum value of co2 (%5.1f ppm) occured in year %d\n",maxco2,
	 year_of_max);


  free_ivector(year,0,N-1);
  free_dvector(co2,0,N-1);

  return(0);
}
