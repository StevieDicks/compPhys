/* Key to Ex 2.10 Reads in grain.dat using a pipe, and then sorts
   the grains into bins.  Uses qsfloat to sort the grains in the file */
#include <stdio.h>
#include "comphys.h"
#include "comphys.c"

int main()
{
  float grain[50];
  int i;
  int bin[10];
  float lower,upper,sum,avegs,sd;

  for(i=0;i<50;i++) scanf("%f",&grain[i]); // Reads from pipe
  for(i=0;i<10;i++) bin[i] = 0; // Initialize bin's to 0.  Important!!

  qsfloat(grain,0,49);
  for(i=0;i<50;i++) printf("%f\n",grain[i]);

  // Sort grains into bins
  for(i=0;i<50;i++) {
    if(grain[i] <= 1.1) bin[0] += 1;
    else if(grain[i] <= 1.2) bin[1] += 1;
    else if(grain[i] <= 1.3) bin[2] += 1;
    else if(grain[i] <= 1.4) bin[3] += 1;
    else if(grain[i] <= 1.5) bin[4] += 1;
    else if(grain[i] <= 1.6) bin[5] += 1;
    else if(grain[i] <= 1.7) bin[6] += 1;
    else if(grain[i] <= 1.8) bin[7] += 1;
    else if(grain[i] <= 1.9) bin[8] += 1;
    else bin[9] += 1;
  }

  for(i=0;i<10;i++) {
    lower = 1.0 + 0.1*(float)i;
    upper = lower + 0.1;
    printf("bin %3.1f to %3.1f has %d grains\n",lower,upper,bin[i]);
  }

  sum = 0.0;
  for(i=0;i<50;i++) sum += grain[i];
  avegs = sum/50.0;

  sum = 0.0;
  // Compute standard deviation
  for(i=0;i<50;i++) sum += (grain[i] - avegs)*(grain[i] - avegs);

  sd = sqrt(sum/50.0);

  printf("The average grain size is %4.2f mm\n",avegs);
  printf("The standard deviation of the distribution is %4.2f mm\n",sd);

  return(0);

}
