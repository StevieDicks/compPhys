#include <stdio.h>
#include <math.h>


int main()
{
  double v0,tf,v;
  const double g = -9.8;

  printf("\nEnter initial velocity, final time(seconds) > ");
  scanf("%lf,%lf",&v0,&tf);

  v = v0 + g*tf;

  printf("\nThe velocity at time %f will be %f\n",tf,v);

  return(0);
}
