/* Key to Ex 2.4  R.O. Gray */

#include <stdio.h>
#include <math.h>

int main()
{
  double t,x,y;
  int i;

  t = 0.0;

  for(i=0;i<=10;i++) {
    x = 5.0 + 0.12*t*t;
    y = 0.02*pow(t,3.0);
    printf("t = %3.1f x = %f  y = %f\n",t,x,y);
    t += 0.5;
  }

  return(0);
}
