#include <stdio.h>
#include <math.h>
int main()
{
  double x1,y1,x2,y2;
  double k1,k2,k3,k4;
  double dx = 0.01;
  /* initial conditions */
  x1 = 0.0;
  y1 = 1.0;
  /* Integrate using fourth-order Runge Kutta from x=0 to x=1 */
  while(x1 <= 1.0 + .5*dx)
    {
      printf("x = %3.1f y = %f\n",x1,y1);
      if(x1 == 1.0) break;
      k1 = (x1 - 1)*y1*y1*dx; //f(x,y)dx
      k2 = (x1 + .5*dx - 1)*(y1 + .5*k1)*(y1 + .5*k1)*dx; //f(x+.5dx,y+.5k1)dx
      k3 = (x1 + .5*dx - 1)*(y1 + .5*k2)*(y1 + .5*k2)*dx; //f(x+.5dx,y+.5k2)dx
      k4 = (x1 + dx - 1)*(y1 + k3)*(y1 + k3)*dx; //f(x+dx, y+k3)dx
      y2 = y1 + (k1 + 2.0*k2 + 2.0*k3 + k4)/6.0; //always the same
      x2 = x1 + dx;
      x1 = x2;
      y1 = y2;
    }
  return(0);
}
