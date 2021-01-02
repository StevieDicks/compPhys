#include <math.h>
#include <stdio.h>

int sgn(double x);
double f(double y);
  
int main() {
  double x1,y1,z1,x2,y2,z2,z0;
  int n = 0;
  double k1,k2,k3,k4,l1,l2,l3,l4;
  double dx = 0.1;
  //double y,a,b,c; //these are only for the interpolation portion
  double m,b,x0,y0; //these are for interpolation
  
  /* initial conditions */
  /* Using x1 as time condition t, where t is the deriving factor (dt) in the problem */
  x1 = 0.0;
  y1 = 3.141592654/4;
  z1 = 0.0;
  
  /* Integrate using fourth-order Runge Kutta for 4 oscillations */
  printf("\nUse 4th Order Runge Kutta for n = 4 oscillations:\n");
  while(n < 4) {
    printf("t = %3.1f y = %f z = %f n = %d\n",x1,y1,z1,n);
    //if(x1 == 1.0) break;
    k1 = z1*dx;
    l1 = (-sin(y1))*dx;
    k2 = (z1+0.5*l1)*dx;
    l2 = -sin(y1+0.5*k1)*dx;
    k3 = (z1+0.5*l2)*dx;
    l3 = -sin(y1+0.5*k2)*dx;
    k4 = (z1+l3)*dx;
    l4 = -sin(y1+k3)*dx;
    y2 = y1 + (k1 + 2.0*k2 + 2.0*k3 + k4)/6.0;
    z2 = z1 + (l1 + 2.0*l2 + 2.0*l3 + l4)/6.0;
    if(sgn(z1) == -sgn(z2)) n++;
    x2 = x1 + dx;
    x0 = x1; //for interpolation
    x1 = x2;
    y0 = y1; //for interpolation
    y1 = y2;
    z0 = z1; //will be used in interpolation step (next phase of code)
    z1 = z2;
  }

  printf("\nMaximize y:\n");
  m = (z1-z0)/(x1-x0);
  b = z0 - m*x0; //this is y-intercept
  printf("%f, %f\n",m,b);
  x0 = fabs(b/m);

  
  /* /\* Here we will maximize y *\/ */
  /* a = z0; */
  /* c = z1; */
  /* b = (a+c)/2; */
  /* y = b; */
  /* while(fabs(a-c) > 1E-6) */
  /*   { */
  /*     if(fabs(b-a) > fabs(c-b)) */
  /* 	{ */
  /* 	  y = (a+b)/2; */
  /* 	  if(f(y) > f(b)) //then the interval is (y,b,c) */
  /* 	    { */
  /* 	      b = y; */
  /* 	    } */
  /* 	  else //the interval is (a,y,b) */
  /* 	    { */
  /* 	      c = b; */
  /* 	      b = y; */
  /* 	    } */
  /* 	} */
  /*     else */
  /* 	{ */
  /* 	  y = (b+c)/2; */
  /* 	  if(f(y) > f(b)) //then the interval is (a,b,y) */
  /* 	    { */
  /* 	      c = y; */
  /* 	    } */
  /* 	  else //the interval ix (b,y,c) */
  /* 	    { */
  /* 	      a = b; */
  /* 	      b = y; */
  /* 	    } */
  /* 	} */
  /*     printf("%lf\n",y); */
  /*   } */
  
  printf("\n y = %f;\n t = %3.1f; \n n(oscillations) = %d.\n\n",y0,x0,n);
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
