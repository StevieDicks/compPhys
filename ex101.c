/* Step function: h = -1 when t<0, h = +1 when t>0. 
   Use Fourier Series to model this.
   (We should use Sine functions b/c the function is odd.) 
   Plot results to GNUplot. */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "comphys.h"
#include "comphys.c"
const double pi = 3.141592654;
double integrate();

int main(){
  double w, T, an, bm, h, t;

  
  h = (4.0/pi)*(sin(t) + (1.0/3.0)*sin(3*t) + (1.0/5.0)*sin(5*t) + (1.0/7.0)*sin(7*t) + (1.0/9.0)*sin(9*t));
  fprintf(out,"%lf %lf\n",t,h);
}

double integrate(){
}
