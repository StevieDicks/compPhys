#include <math.h>
#include <stdio.h>

int sgn(double x);
double f(double y);
  
int main() {
  double x,y,z,y2,z2;
  double k1,k2,k3,k4,l1,l2,l3,l4;
  double dx = 0.05;
  double a,b,c,d,k;
  FILE *outy,*outz,*rsp;
  
  /* initial conditions */
  /* Using x1 as time condition t, where t is the deriving factor (dt) in the problem */

  if((outy = fopen("dicksonsb_exam3_2y.dat","w")) == NULL) {
    printf("\nCannot open file for output\n");
    exit(1);
  }
  if((outz = fopen("dicksonsb_exam3_2z.dat","w")) == NULL) {
    printf("\nCannot open file for output\n");
    exit(1);
  }
  
  x = 0.0;
  y = 1.0;
  z = 4.25;

  a = 3.0;
  b = 1.0;
  c = 2.0;
  d = 0.3;
  k = 100;
  
  /* Integrate using fourth-order Runge Kutta for 4 oscillations */
  while(x <= 50+.5*dx) {
    fprintf(outy,"%f %f\n",x,y);
    fprintf(outz,"%f %f\n",x,z);
    if(x == 50.0) break;
    k1 = (a*z*(1-z/k) - b*z*y)*dx;
    l1 = (-c*y + d*z*y)*dx;
    k2 = (a*(z+0.5*l1)*(1-(z+0.5*l1)/k) - b*(z+0.5*l1)*(y+0.5*k1))*dx;
    //should be "(a*(z+0.5*l1*dx)...);
    l2 = (-c*(y+0.5*k1) + d*(z+0.5*l1)*(y+0.5*k1))*dx;
    k3 = (a*(z+0.5*l2)*(1-(z+0.5*l2)/k) - b*(z+0.5*l2)*(y+0.5*k2))*dx;
    l3 = (-c*(y+0.5*k2) + d*(z+0.5*l2)*(y+0.5*l2))*dx;
    k4 = (a*(z+l3)*(1-(z+l3)/k) - b*(z+l3)*(y+k3))*dx;
    l4 = (-c*(y+k3) + d*(z+l3)*(y+k3))*dx;
    y2 = y + (k1 + 2.0*k2 + 2.0*k3 + k4)/6.0;
    z2 = z + (l1 + 2.0*l2 + 2.0*l3 + l4)/6.0;
    x += dx;
    y = y2;
    z = z2;
  }

  fclose(outy);
  fclose(outz);

  if((rsp = fopen("gnuplot.rsp","w"))==NULL) {
    printf("\nCannot open gnuplot.rsp for writing\n");
    exit(1);
  }
  fprintf(rsp,"plot 'dicksonsb_exam3_2y.dat' using 1:2 with lines,'dicksonsb_exam3_2z.dat' using 1:2 with lines\n");
  fprintf(rsp,"pause mouse\n");
  fprintf(rsp,"replot\n");
  fclose(rsp);
  if(system("gnuplot gnuplot.rsp") == -1) {
    printf("\nCommand could not be executed\n");
    exit(1);
  }

  return(0);
}


int sgn(double x){
  if(x > 0) return(1);
  if(x < 0) return(-1);
  if(x == 0){
    return(0);
  }
  return(0);
}

double f(double y){
  return(-sin(y));
}
