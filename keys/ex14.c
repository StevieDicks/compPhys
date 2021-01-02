/* Coulomb Exercise */
#include <stdio.h>
#include <math.h>

const double pi=3.141592653589793;
const double eps0 = 8.85418782e-12;

int main()
{
  double x=0.0,y=0.0;
  int ni=0;
  double Q1= 4.54,Q2=3.883;
  double r,Fx,Fy,FT;

  printf("\nThis program will print the x and y components of the Coulomb force on charge Q2\n");

  while((x == 0.0 && y == 0.0) || ni != 2) {
    printf("\nEnter x,y coordinates for Q2, avoiding 0,0 > ");
    ni = scanf("%lf,%lf",&x,&y);
    if(x == 0.0 && y == 0.0)
     printf("\nBoth x and y cannot be 0.0; please try again");
    if(ni != 2) printf("\nEnter x and y values separated by a comma\n");
  }

  /* Compute the total force */

  r = sqrt(x*x + y*y);
  FT = (Q1*Q2)/(4.0*pi*eps0*r*r);

  /* Compute the two components of the force here.  Remember that like
     charges repel! */

  Fx = (x/r)*FT;
  Fy = (y/r)*FT;

  printf("Fx = %e newtons\n",Fx);
  printf("Fy = %e newtons\n",Fy);

  return(0);
}
