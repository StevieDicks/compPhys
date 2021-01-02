/* Key for Exercise 1.7,  R.O. Gray */
#include <stdio.h>
#include <math.h>

int main()
{
  double L = 3.839e26;
  double a,R,T;
  double sig = 5.671e-8;
  int ni;
  double pi = 3.141592654;

  printf("Enter the distance from the planet to sun (meters) > ");
  ni = scanf("%le",&R);
  printf("Enter the albedo of the planet (0 - 1) > ");
  ni = scanf("%lf",&a);

  T = pow((L*(1-a))/(16*pi*sig*R*R),0.25);

  printf("Planck Surface temperature (K) = %5.2f\n",T);

  return(0);
}
