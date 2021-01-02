/* Ex 1.7 Basic "Climate" Model */

#include <stdio.h>
#include <math.h>

int main(){
  const double pi = 3.141592654;
  const double L = 3.839*pow(10,26);
  double a,R,T;
  const double s = 5.671*pow(10,-8); //s is for sigma
  int ni;

  printf("\nThis program calculates the blackbody temperature of a planet\nassuming no atmosphere. Please input the the albedo, 'a', \nand the radius from the sun, 'R':\n(a,R): ");
  scanf("%lf,%lf",&a,&R);

  T = pow(((L*(1-a))/(16*pi*s*R*R)),.25);
  printf("\nThe blackbody temperature of this planet is %10lf.\n\n",T);
}
