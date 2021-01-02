#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double deltaT(int date, double pco2);

int main(){
  int ni;
  FILE *in,*out,*rsp;
  char outfile[80];
  double dT;
  double pco2 = 0.0;
  int date;


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
  
  while (fscanf(in,"%d %lf",&date,&pco2) != EOF) {  //read in one line until end of file
    dT = deltaT(date,pco2);               //compute dT from function deltaT
    fprintf (out,"%d  %f\n",date,dT);   //print to output file until EOF
  }

  fclose(in);
  fclose(out); 

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
  return(0);
}

double deltaT(int date, double pco2){
  double T;
  T = 2.5 * (pco2 - 365.0) / 280.0;
  return(T);
}
