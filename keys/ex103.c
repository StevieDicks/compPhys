/* Ex 10.3 -- a low-pass filter for cleaning data files */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "comphys.h"
#include "comphys.c"

int main()
{
  float *x,*y;
  float x1,y1;
  float sum,sum1;
  unsigned long n,m,z,k,i;
  FILE *in,*out;
  char outfile[80];

  if((in = fopen("UHA21.nor","r")) == NULL) {
    printf("\nCannot open UHA21.nor\n");
    exit(1);
  }

  printf("\nEnter number of high frequency points to zero out in transform\n");
  printf("of UHA21.nor > ");
  scanf("%ld",&z);

  printf("\nEnter output file name > ");
  scanf("%s",outfile);

  if((out = fopen(outfile,"w")) == NULL) {
    printf("\nCannot open %s\n",outfile);
    exit(1);
  }

  /* Count the number of points in the input file */
  n = 0;
  while(fscanf(in,"%f %f",&x1,&y1) != EOF) n++;
  fclose(in);

  /* Find first power of 2 greater than or equal to n */
  m = 1;
  while(m<n) m*= 2;

  printf("m = %ld\n",m);

  x = vector(1,m);
  y = vector(1,m);

  in = fopen("UHA21.nor","r");

  k = 1;
  while(fscanf(in,"%f %f",&x[k],&y[k]) != EOF) k++;
  fclose(in);

  /* zeropad if necessary */
  for(i=n+1;i<=m;i++) y[i] = 0.0;

  /* Calculate total power */
  sum = 0.0;
  for(i=1;i<=m;i++) sum += y[i];

  /* Transform */
  realft(y,m,1);

  /* Zero out high frequency tail */
  for(i=m-z;i<=m;i++) y[i] = 0.0;

  /* Inverse transform */
  realft(y,m,-1);

  sum1 = 0.0;
  for(i=1;i<=m;i++) sum1 += y[i];

  /* Restore power */
  for(i=1;i<=m;i++) y[i] *= sum/sum1;

  for(i=1;i<=n;i++) fprintf(out,"%f %f\n",x[i],y[i]);

  fclose(out);

  /* Deallocate space */
  free_vector(x,1,m);
  free_vector(y,1,m);
  
  return(0);
}
