/* R.O. Gray.  Key to Problem 2 of Exam 3.  Predator/prey interaction */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

main()
{
  double x1,x2,y1,y2,t1,t2,dt;
  double a,b,c,d,k;
  double k1,k2,k3,k4,l1,l2,l3,l4;
  int err;
  FILE *out,*rsp;

  out = fopen("output2.dat","w");
  if(out == NULL) {
    printf("Cannot open output file\n");
    exit(1);
  }

  // Constant definitions

  x1 = 4.25;
  y1 = 1.0;
  a = 3.0;
  b = 1.0;
  c = 2.0;
  d = 0.3;
  k = 100.0;
  t1 = 0.0;
  dt = 0.05;

  fprintf(out,"%f %f %f\n",t1,x1,y1);

  // Integration of two interleaved R-K systems

  while(t1 <= 50.0) {
    k1 = a*x1*(1-x1/k) - b*x1*y1;
    l1 = -c*y1 + d*x1*y1;
    k2 = a*(x1 + 0.5*k1*dt)*(1-(x1+0.5*k1*dt)/k) - b*(x1+0.5*k1*dt)*(y1+0.5*l1*dt);
    l2 = -c*(y1+0.5*l1*dt) + d*(x1+0.5*k1*dt)*(y1+0.5*l1*dt);
    k3 = a*(x1 + 0.5*k2*dt)*(1-(x1+0.5*k2*dt)/k) - b*(x1+0.5*k2*dt)*(y1+0.5*l2*dt);
    l3 = -c*(y1+0.5*l2*dt) + d*(x1+0.5*k2*dt)*(y1+0.5*l2*dt);
    k4 = a*(x1 + k3*dt)*(1-(x1+k3*dt)/k) - b*(x1+k3*dt)*(y1+l3*dt);
    l4 = -c*(y1+l3*dt) + d*(x1+k3*dt)*(y1+l3*dt);
    x2 = x1 + (k1 + 2.0*k2 + 2.0*k3 + k4)*dt/6.0;
    y2 = y1 + (l1 + 2.0*l2 + 2.0*l3 + l4)*dt/6.0;
    t2 = t1 + dt;
    fprintf(out,"%f %f %f\n",t2,x2,y2);
    x1 = x2;
    y1 = y2;
    t1 = t2;
  }
  fclose(out);

  // Plot the results
  rsp = fopen("gnuplot.rsp","w");
  if(rsp == NULL) {
    printf("\nCannot open response file\n");
    exit(1);
  }
  fprintf(rsp,"plot 'output2.dat' using 1:2 with lines\n");
  fprintf(rsp,"replot 'output2.dat' using 1:3 with lines\n");
  fprintf(rsp,"pause mouse\n");
  fprintf(rsp,"replot\n");
  fclose(rsp);
  err = system("gnuplot gnuplot.rsp");
  if(err == -1) {
    printf("Gnuplot command could not be executed\n");
    exit(1);
  }
  return(0);

}
