#include <stdio.h>
#include <math.h>

int main()
{
  double V,Vo,tf;
  double g = -9.8;
  int ni;

  printf("\nPlease enter the initial velocity, Vo [m/s],\nand final time, tf [s], separated by a comma.\n>");
  ni = scanf("%lf,%lf",&Vo,&tf);
  V = Vo + g*tf;
  printf("\nThe final velocity is %f m/s.\n\n",V);
}
