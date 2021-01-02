/* differential equation for isothermal gas sphere */
/*
  ddp/ddr - (1/p)(dp/dr)^2 + (2/r)(dp/dr) + p^2 = 0
  y == p;
  t == r;
  z == dp/dr;
*/

#include <stdio.h>
#include <stdlib.h>
#include "comphys.c"
#include "comphys.h"
double pi = 3.14159265358979323846;

float p(float r);
float pp(float r);
double trap(double a, double b, double (*func)(double), int N);
double integrand(double y);

int main() {
  double t1,y1,z1,t2,y2,z2;
  double k1,k2,k3,k4,l1,l2,l3,l4;
  double dt = 0.1;
  double m,t,y,z;
  int N = 20;
  double Mr;
  FILE *out, *rsp;

  out = fopen("dicksonsb_final_2.out","w");

  /* initial conditions */
  t1 = 0.1;
  y1 = p(t1);
  z1 = pp(t1);
  //printf("\n r      p        p'\n");
  //printf("0.0 1.000000 0.000000\n");
  fprintf(out,"0.000000 1.000000\n");

/* Integrate using fourth-order Runge Kutta. */

  while(t1 <= 6.0) {
    //printf("%.1f %f %f\n",t1,y1,z1);
    fprintf(out,"%f %f\n",t1,y1);
    k1 = z1*dt;
    l1 = ((z1*z1)/y1 - (2*z1)/y1 - y1*y1)*dt;
    k2 = (z1+0.5*l1)*dt;
    l2 = (((z1+0.5*l1)*(z1+0.5*l1))/(y1+0.5*k1) - (2*(z1+0.5*l1)/t1) - (y1+0.5*k1)*(y1+0.5*k1))*dt;
    k3 = (z1+0.5*l2)*dt;
    l3 = (((z1+0.5*l2)*(z1+0.5*l2))/(y1+0.5*k2) - (2*(z1+0.5*l2)/t1) - (y1+0.5*k2)*(y1+0.5*k2))*dt;
    k4 = (z1+l3)*dt;
    l4 = (((z1+l3)*(z1+l3))/(y1+k3) - (2*(z1+l3)/t1) - (y1+k3)*(y1+k3))*dt;
    y2 = y1 + (k1 + 2.0*k2 + 2.0*k3 + k4)/6.0;
    z2 = z1 + (l1 + 2.0*l2 + 2.0*l3 + l4)/6.0;
    t2 = t1 + dt;
    
    t1 = t2;
    y1 = y2;
    z1 = z2;
  }

  
  /* Integration portion */
  // integrate Mr = integral(r^2 * p dr), (0,r)
  Mr = trap(0, 6.0,integrand,N);

  printf("\noutput file \"dicksonsb_final_2.out\" includes the density as a function of radius\nTotal mass interior to r = 6 := %lf\n\n",Mr);
  
  fclose(out);
  
  return(0);
}

float p(float r) {
  return( 1 - (r*r/6) + (r*r*r*r/45) - (61*r*r*r*r*r*r/22680) + (629*r*r*r*r*r*r*r*r/2041200));
}

float pp(float r) {
  return( -(r/3) + (4*r*r*r/45) - (61*6*r*r*r*r*r/22680) + (629*8*r*r*r*r*r*r*r/2041200));
}


double trap(double a, double b, double (*func)(double), int N) {
  double h,integral,x;
  int i;
  if(a == b) return(0.0);
  h = (b-a)/(double)(N-1);
  integral = 0.0;
  integral += 0.5*((*func)(a) + (*func)(b)); x = a+h;
  for(i=2;i<N;i++) {
    integral += (*func)(x);
    x += h; }
  integral *= h;
  return(integral);
}

double integrand(double r) {
  return(r*r*p(r));
}
