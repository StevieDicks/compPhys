/* Ex3.5: This program reads in wavelengths from inputwave.dat,
   calculates the Planck function at those wavelengths, and outputs the
   results to a file  */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double planck(double wave, double T);

int main()
{
  double wave,T;
  double result;
  char outfile[80];
  FILE *in,*out;

  printf("\nEnter the temperature in Kelvin > ");
  scanf("%lf",&T);
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


  while(fscanf(in,"%lf",&wave) != EOF) {
    result = planck(wave,T);
    fprintf(out,"%7.1f  %e\n",wave,result);
  }

  fclose(in);
  fclose(out);

  return(0);
}

double planck(double wave, double T)
{
  static double p = 1.19106e+27;
  double p1;

  p1 = p/(pow(wave,5.0)*(exp(1.43879e+08/(wave*T)) - 1.0));
  return(p1);
}
