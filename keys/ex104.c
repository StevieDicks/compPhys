/* Exercise 10.4 key: R.O. Gray */
#include <stdio.h>
#include <math.h>
#include "comphys.h"
#include "comphys.c"

int main()
{
  float *data,*respns,*ans;
  float t,dt = 0.1;
  float h,r,sum=0.0;
  int i;
  float R = 1.0;
  float C = 1.0;
  FILE *out;

  data = vector(1,128);
  respns = vector(1,128);
  ans = vector(1,256);

  /* Define h(t) */
  t = -6.4;
  for(i=1;i<=128;i++) {
    if(t >= 0.0 && t <= 1.0) data[i] = 1.0;
    else data[i] = 0.0;
    t += dt;
  }

  /* Define response function -- note wrapping of negative part to
     second half of vector */
  t = 0.0;
  for(i=1;i<=64;i++) {
    respns[i] = exp(-t/(R*C));
    t += dt;
  }
  for(i=65;i<=128;i++) respns[i] = 0.0;

  convlv(data,128,respns,128,1,ans);

  /* Print out convolved function */

  if((out = fopen("ex104.out","w")) == NULL) {
    printf("\nCannot open ex104.out for writing\n");
    exit(1);
  }

  t = -6.4;
  for(i=1;i<=128;i++) {
    if(t >= 0.0 && t <= 1.0) h = 1.0;
    else h = 0.0;
    if(t >= 0.0) r = exp(-t/(R*C));
    else r = 0.0; 
    fprintf(out,"%f %f %f %f\n",t,ans[i]/64.0,r,h);
    t += dt;
  }
  fclose(out);

  free_vector(data,1,128);
  free_vector(respns,1,128);
  free_vector(ans,1,256);

  return(0);
}
