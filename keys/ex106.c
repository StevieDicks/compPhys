/* Ex 10.6 Key  R.O. Gray */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "comphys.h"
#include "comphys.c"

int main()
{
  float *t1,*t2,*x,*y,*ans;
  FILE *in1,*in2,*out,*rsp;
  int i,ni,j;
  char indata1[60];
  char indata2[60];

  printf("\nEnter the name of the first datafile > ");
  ni = scanf("%s",indata1);
  printf("\nEnter the name of the second datafile > ");
  ni = scanf("%s",indata2);



  in1 = fopen(indata1,"r");
  in2 = fopen(indata2,"r");

  if(in1 == NULL || in2 == NULL) {
    printf("\nProblem opening one or both data files\n");
    exit(1);
  }
  out = fopen("corr1.dat","w");
  if(out == NULL) {
    printf("\nProblem opening output file\n");
    exit(1);
  }

  t1 = vector(1,1024);
  t2 = vector(1,1024);
  x = vector(1,1024);
  y = vector(1,1024);
  ans = vector(1,2048);

  /* Read in the two data files */
  for(i=1;i<=1024;i++) {
    fscanf(in1,"%f %f",&t1[i],&x[i]);
    fscanf(in2,"%f %f",&t2[i],&y[i]);
  }

  correl(x,y,1024,ans);


  /* Print out the correlation, taking into account it is in wrap-around
     format in ans */
  for(i=512;i<=1024;i++) {
    j = i-1024;
    fprintf(out,"%d %f\n",j,ans[i]);
  }
  for(i=1;i<512;i++) fprintf(out,"%d %f\n",i,ans[i]);

  fclose(in1);
  fclose(in2);
  fclose(out);


  /* Plot out the correlation using gnuplot */
  if((rsp = fopen("gnuplot.rsp","w")) == NULL) {
    printf("\nCannot open gnuplot.rsp for writing\n");
    exit(1);
  }
  fprintf(rsp,"plot 'corr1.dat' using 1:2\n");
  fprintf(rsp,"pause mouse\n");
  fprintf(rsp,"replot\n");
  fclose(rsp);
  if(system("gnuplot gnuplot.rsp") == -1) {
    printf("\nCommand could not be executed\n");
    exit(1);
  }

  return(0);
}
 
