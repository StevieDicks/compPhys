#include <stdio.h>
#include <math.h>
int flag = 0;
double integrate(double x1,double y1,double z1,double y11);

int main() {
  double x1,y1,z1,z2,z3,y11,r,r1,r2,r3;
  
  /* initial conditions: (z’s are trial y’(0)'s) */
  x1 = 0.0;
  y1 = 1.0;
  z1 = 0.0;
  z2 = 1.0;
  /* Enter boundary condition at the end point and put into y11 */
  printf("\ny(0) = 1.0;\nEnter y(1):= ");
  scanf("%lf",&y11);
  
  /* Iterative loop - stop condition is when last two iterations are equal within machine precision */
  while(fabs(z1-z2) > 1.0e-06) {
    r1 = integrate(x1,y1,z1,y11);
    r2 = integrate(x1,y1,z2,y11);
    
    /* The interpolation (extrapolation) equation to find
       a better z = z3 */
    z3 = z1 - r1*(z2-z1)/(r2-r1);
    
    /* Replace the worst trial y’(0) with the
       best found so far */
    
    if(fabs(z3-z1) > fabs(z3-z2)) z1 = z3;
    else z2 = z3;
  }
  printf("y’(0) = %f\n",z1);
  flag = 1;
  printf("x = %3.1f, y = %f, y' = %f\n",x1,y1,z1);
  r = integrate(x1,y1,z1,y11);
  return 0;
}


double integrate(double x1,double y1,double z1,double y11) {
  /* Integrate Van der Pol equation using fourth-order Runge Kutta from x=0 to x=1. The return value is y(1) - y11 where y11 is the second boundary condition. The correct solution will have y(1) - y11 = 0 */
  double dx = 0.1;
  double x2,y2,z2;
  double k1,k2,k3,k4,l1,l2,l3,l4;
  extern int flag;
  
  while(x1 < (1.0 - dx/2.0)) {
    k1 = z1*dx;
    l1 = (2*y1*y1 + x1)*y1*dx;
    k2 = (z1+0.5*l1)*dx;
    l2 = (2*(y1+0.5*k1)*(y1+0.5*k1)+ x1*(y1+0.5*k1))*dx;
    k3 = (z1+0.5*l2)*dx;
    l3 = (2*(y1+0.5*k2)*(y1+0.5*k2)+ x1*(y1+0.5*k2))*dx;
    k4 = (z1+l3)*dx;
    l4 = ((1-(y1+k3)*(y1+k3))*(z1+l3)-(y1+k3))*dx;
    y2 = y1 + (k1 + 2.0*k2 + 2.0*k3 + k4)/6.0;
    z2 = z1 + (l1 + 2.0*l2 + 2.0*l3 + l4)/6.0;
    x2 = x1 + dx;
    x1 = x2;
    y1 = y2;
    z1 = z2;
    if(flag == 1) printf("x = %4.2f, y = %f, y' = %f\n",x1,y1,z1);
  }
  return(y1-y11);
}
