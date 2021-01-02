#include <math.h>
#include <stdio.h>

int main(){
  const double dx = 1.0*pow(10,-7);
  double x1=0;
  double x0=0;
  double x2=0;
  double x3=0;
  int ni;

  printf("\nPlease enter an estimate of a root for x^2 = 5 + 2/x. \n This program will find the root using iterations with\n a precision of 1.0e-7.\nFor the positive root enter a positive number first\n and vice versa for the negative root.\n> ");
  ni = scanf("%lf",&x0);

  while(x0==0){
    printf("Please enter a number that is not 0.\n> ");
    //HOW do I repeat the prompt if someone does enter a 0??
    ni = scanf("%lf",&x0);
  }
  
  while(fabs(x1-x0) > dx){
    x1 = 5 + 2/x0;         //x1 is going to be 
    // x3 = x1;
    x2 = 5+ 2/x1;
    x0 = x2;
  }
  
  if(x1>0){
    printf("The positive root is %lf.\n",x1);
  }else if(x1<0 || x2<0){
    printf("The negative root is %lf.\n",x1);
  }else{
    printf("Error\n");
  }
  return(0);
}
