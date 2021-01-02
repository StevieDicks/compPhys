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
  float r[1000];
  int a,b,c,d;

  /* Use the time function to supply a different seed to the
     random number generator every time the program is run */

  now = time(NULL);

  idum = -1*now;

  /* Initialize random number generator	*/

  rn = ran1(&idum);

  /* Now you can generate any number of random numbers between 0.0
     and 1.0 with statements like the following */

  x = ran1(&idum);


  for(i=1;i<=1000;i++){
    x = ran1(&idum);
    r[i] = x;
    if(r[i]<.25){
      a++;
    }else if(r[i]<.50){
      b++;
    }else if(r[i]<.75){
      c++;
    }else if(r[i]<1.0){
      d++;
    }
  }

  printf("\nThere are:\n%d numbers greater than or equal to 0 and less than 0.25,\n%d numbers greater than or equal to .25 and less than .50,\n%d numbers greater than or equal to .50 and less than .75, and\n%d numbers greater than or equal to .75 and less than 1.\n\n",a,b,c,d);
  
}
