#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "comphys.c"
#include "comphys.h"


int main(){
  int ni;
  int i = 0;
  FILE *in,*out,*rsp;
  char outfile[80];

  int *date;
  double *co2;


  date = ivector(0,511); //use 511 because it is definitely larger than
  co2 = dvector(0,511);  //    the number of lines in the file
                         //    (EOF will stop the read/write WHILE function)

  printf("\nEnter the name of the output file > ");
  ni = scanf("%s",outfile);

  if((out = fopen(outfile,"w")) == NULL) {
    printf("\nCannot open %s for writing\n",outfile);
    exit(1);
  }

  if((in = fopen("vostok_co2.dat","r")) == NULL) {
    printf("\nCannot open file for input\n");
    exit(1);
  }

  while (fscanf(in,"%d   %lf",&date[i],&co2[i]) != EOF) {
    fprintf(out,"%d %lf\n",date[i],co2[i]);
    i++;
  }

  fclose(in);
  fclose(out);
  
  /* Now the data has all been read in we can continue with the rest of the program: take the min/max of co2 and print those values to screen plus the corresponding dates. Calculate the average co2 concentration between 112,000 and 130,000 years ago, and between 138,000 and 175,000 years ago */

  
  if((rsp = fopen("gnuplot.rsp","w"))==NULL) {
    printf("\nCannot open gnuplot.rsp for writing\n");
    exit(1);
  }
  fprintf(rsp,"plot '%s' using 1:2 with lines\n",outfile);
  fprintf(rsp,"pause mouse\n");
  fprintf(rsp,"replot\n");
  fclose(rsp);
  if(system("gnuplot gnuplot.rsp") == -1) {
    printf("\nCommand could not be executed\n");
    exit(1);
  }

  for (i=0;i<511;i++){
    
  }


  free_ivector(date,0,511);
  free_dvector(co2,0,511);
  return(0);
}
