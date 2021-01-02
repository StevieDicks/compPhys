/* Key for Problem 1, Exam 1, Fall 2016
   Just a basic kinematics problem
 */
#include <stdio.h>
#include <math.h>
double eps = 1.0e-7;

int main()
{
  double m,b;
  double t = 0.0;
  double g = 9.8;
  double v = 0.0;
  double vt;
  int n = 0;
  int ni;

  printf("\nEnter values for m and b (comma delimited) > ");
  ni = scanf("%lf,%lf",&m,&b);

  vt = -m*g/b;   // Terminal velocity

  while(fabs(v-vt) > eps ) {            // Stop when v gets within eps of vt
    v = -m*g*(1.0 - exp(-b*t/m))/b;
    printf("t = %4.0f v = %lf\n",t,v);
    t += 1.0;
    n++;
    if(n > 100) break;  // Stop after n loops, even if vt not attained.
  }

  return(0);
}
