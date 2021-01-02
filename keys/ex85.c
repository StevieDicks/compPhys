/* Ex 8.5 R.O. Gray: Integration of the differential equation for the
   simple pendulum over two complete oscillations */

#include <stdio.h>
#include <math.h>
double pi = 3.14159265358979323846;

int main()
{
  double t1,y1,z1,t2,y2,z2;
  double k1,k2,k3,k4,l1,l2,l3,l4;
  double dt = 0.1;
  double m,t,y,z;
  int P = 0;

  /* initial conditions */
  t1 = 0.0;
  y1 = pi/4.0;
  z1 = 0.0;

/* Integrate using fourth-order Runge Kutta.  P counts the number of 
oscillations; stop after 2 complete oscillations */

  while(P < 2) {
    printf("%12.10f %f %f %d\n",t1,y1,z1,P);
    k1 = z1*dt;
    l1 = -sin(y1)*dt;
    k2 = (z1+0.5*l1)*dt;
    l2 = -sin(y1+0.5*k1)*dt;
    k3 = (z1+0.5*l2)*dt;
    l3 = -sin(y1+0.5*k2)*dt;
    k4 = (z1+l3)*dt;
    l4 = -sin(y1+k3)*dt;
    y2 = y1 + (k1 + 2.0*k2 + 2.0*k3 + k4)/6.0;
    z2 = z1 + (l1 + 2.0*l2 + 2.0*l3 + l4)/6.0;
    t2 = t1 + dt;
    /* Increment P when the angular velocity changes sign from + to - */
    if(z1 > 0.0 && z2 <= 0.0) P++;
    if(P == 2) {
      /* Print out time when P completes second swing */
      m = (z2-z1)/(t2-t1);
      t = (m*t1-z1)/m;
      y = pi/4.0;
      z = 0.0;
      printf("%12.10f %f %f %d\n",t,y,z,P);
      break;
    }
    t1 = t2;
    y1 = y2;
    z1 = z2;
  }

  return(0);
}
