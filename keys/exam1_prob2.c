/* Key for Prob 2, Exam 1, Fall 2016 */
#include <stdio.h>
#include <stdlib.h> /* needed for exit() */

int main()
{
  double flux[1024],wave[1024];
  double maxflux,wavemax=0;
  FILE *in,*out,*rsp;
  int i,k;

  //Open and check input and output streams

  if((in = fopen("hip17695.flx","r")) == NULL) {
    printf("\nCannot find input file\n");
    exit(1);
  }

  if((out = fopen("normal.dat","w")) == NULL) {
    printf("\nCannot open output file\n");
    exit(1);
  }

  //Read in data, find the maximum flux value and divide through by it.
  maxflux = 0.0;

  k = 0;
  while(fscanf(in,"%lf %le",&wave[k],&flux[k]) != EOF) {
    if(maxflux < flux[k]) {
       maxflux = flux[k];
       wavemax = wave[k];
    }
    k++;
  }

  fclose(in);

  // Normalize the fluxes
  for(i=0;i<k;i++) flux[i] /= maxflux;

  // print normalized fluxes out to the output file
  for(i=0;i<k;i++) fprintf(out,"%f %f\n",wave[i],flux[i]);

  fclose(out);

  printf("Maximum flux occurs at wavelength %8.3f\n",wavemax);

  //Plot with gnuplot -- you didn't need to do this, but here it is

  if((rsp = fopen("gnuplot.rsp","w")) == NULL) {
    printf("\nCannot open gnuplot.rsp for writing\n");
    exit(1);
  }
  fprintf(rsp,"plot 'normal.dat' using 1:2 with lines\n");
  fprintf(rsp,"pause mouse\n");
  fprintf(rsp,"replot\n");
  fclose(rsp);
  if(system("gnuplot gnuplot.rsp") == -1) {
    printf("\nCommand could not be executed\n");
    exit(1);
  }




  return(0);
}
