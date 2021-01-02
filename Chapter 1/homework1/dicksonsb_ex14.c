#include <stdio.h>
#include <math.h>

const double pi = 3.141592653589793;

int main(){
  double F;
  double x=0.0,y=0.0;
  double Q1=4.54,Q2=3.883;
  int ni = 0;
  double k=8.9875*pow(10,9);

  printf("\nThis program will print the x and y components of the Coulomb force on charge Q2\n");

  while(x==0.0 && y==0.0) {
    printf("\nEnter x,y coordinates for Q2, avoiding 0,0 > ");
    ni = scanf("%lf,%lf",&x,&y);
    if(x==0.0 && y==0.0)
      printf("\nBoth x and y cannot be 0.0; please try again");
  }

  F=k*Q1*Q2/(x*x+y*y);
  printf("\nThe Coulomb force, F = %lf\n",F);
  
  return(0);
}
