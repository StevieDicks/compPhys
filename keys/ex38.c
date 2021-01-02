/* Ex3.7: This program reads in wavelengths from inputwave.dat into a vector
wave and calculates the Planck function at those wavelengths */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "comphys.h"
#include "comphys.c"

int main()
{
  float T;
  float *wave;
  float result;
  char outfile[80];
  FILE *in,*out;
  int i,k;

  /* Allocate a reasonable amount of space for wave */
  wave = vector(0,40);

  printf("\nEnter the temperature in Kelvin > ");
  scanf("%f",&T);
  printf("\nEnter the name of the output file > ");
  scanf("%s",outfile);

  if((in = fopen("inputwave.dat","r")) == NULL) {
    printf("\nCannot open inputwave.dat for reading\n");
    exit(1);
  }

  if((out = fopen(outfile,"w")) == NULL) {
   printf("\nCannot open %s for writing\n",outfile);
   exit(1);
  }

  k = 0;
  while(fscanf(in,"%f",&wave[k]) != EOF) k++;

  for(i=0;i<k;i++) {
    result = planck(wave[i],T);
    fprintf(out,"%7.1f  %e\n",wave[i],result);
  }

  fclose(in);
  fclose(out);

  return(0);
}
