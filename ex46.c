/* Hydrogen Partition Function */
// Example of matrix usage

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double partf(double x1, double x2);
double y;
double x1;
int x2;

int main(){
  //double U[][];
  //int T[];
  //double E[];
  int ni;


  printf("Please enter value for delta E, the change in energy level\nbetween .10 and 2.00: > ");
  ni = scanf("%lf",&x1);
  while(x1 < .10 || x1 > 2.00){
    printf("Please enter value for delta E, the change in energy level\nbetween .10 and 2.00: > ");
    ni = scanf("%lf",&x1);
  }
  printf("Please enter value for T, the Temperature of the plasma\nbetween 3250 and 25480: > ");
  ni = scanf("%d",&x2);
  while(x2 < 3250 || x2 > 25480){
    printf("Please enter value for T, the Temperature of the plasma\nbetween 3250 and 25480: > ");
    ni = scanf("%d",&x2);
  }

  
  partf(x1,x2);

  printf("\nU = %2.3lf.\n",y);


  printf("\nMore values:\n   (T, dE): U = ...\n");

  x2=16000;
  x1=0.25;
  partf(x1,x2);
  printf("(16000, 0.25): U = %2.3lf.\n",y);

  x2=18500;
  x1=1.50;
  partf(x1,x2);
  printf("(18500, 1.50): U = %2.3lf.\n",y);

  x2=19000;
  x1=0.15;
  partf(x1,x2);
  printf("(19000, 0.15): U = %2.3lf.\n",y);

  x2=25023;
  x1=1.99;
  partf(x1,x2);
  printf("(25023, 1.99): U = %2.3lf.\n",y);

  return(0);
}


double partf(double x1, double x2){
  double t;
  int u;
  double y1,y2,y3,y4;
  int i,j,n;
  
  double U[9][4] = {{2.000, 2.000, 2.000, 2.000},
		    {2.000, 2.000, 2.000, 2.000},
		    {2.025, 2.006, 2.005, 2.004},
		    {2.068, 2.016, 2.012, 2.009},
		    {2.168, 2.037, 2.027, 2.020},
		    {2.384, 2.080, 2.058, 2.040},
		    {2.814, 2.162, 2.114, 2.078},
		    {3.610, 2.308, 2.213, 2.142},
		    {4.991, 2.551, 2.377, 2.246}};
  double E[4] = {0.10, 0.50, 1.00, 2.00};
  int T[9] = {3250, 10083, 14188, 15643, 17246, 19014, 20963, 23111, 25480};


  
  i=0;
  for(n=0;n<=9;n++) {
    if(E[n] < x1 && E[n+1] >= x1) {
      i=n;
      break;
    }
  }

  
  j=0;
  for(n=0;n<=9;n++) {
    if(T[n] < x2 && T[n+1] >= x2) {
      j=n;
      break;
    }
  }

  y1 = U[j][i];
  y2 = U[j][i+1];
  y3 = U[j+1][i+1];
  y4 = U[j+1][i];


  t = (x1 - E[i])/(E[i+1] - E[i]);
  u = (x2 - T[j])/(T[j+1] - T[j]);

  y = (1-t)*(1-u)*y1 + t*(1-u)*y2 + t*u*y3 + (1-t)*u*y4;
  return(y);
}
