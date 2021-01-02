/* Key for Ex 2.9  This program generates random numbers between 0 and
   1 and then sorts them into four bins depending on the value. */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "comphys.h"
#include "comphys.c"

int main()
{
  long idum = -1;
  time_t now;
  float x,rn;
  int i;
  int bin[4];

  now = time(NULL);
  idum = -1*now;
  rn = ran1(&idum);

  /* Initialize bins to 0 */
  for(i=0;i<4;i++) bin[i] = 0;

  /* Test and increment bins */
  for(i=0;i<1000;i++) {
    x = ran1(&idum);  // Generate the random number, then sort into bins
    if(x <= 0.25) bin[0] += 1;
    else if(x <= 0.50) bin[1] += 1;
    else if(x <= 0.75) bin[2] += 1;
    else bin[3] += 1;
  }

  for(i=0;i<4;i++) printf("bin %d has a count of %d\n",i+1,bin[i]);

  return(0);
}
