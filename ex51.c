#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int sgn(double y);
double f(double x);

int main()
{
  int sgna0, sgnb0, sgnmid0;
  double fa, fb;
  double mid,mid0;
  double x0,x1;
  double a0 = 3;
  double b0 = 4;
  double a=0,b=0;
  double eps = 1E-6;
  
  
  printf("Please enter a guess of boundaries a and b for the root \n> a,b = ");
  ni = scanf("%lf,%lf",&a0,&b0);

  a=a0;
  b=b0;

  a0 = f(a0);
  b0 = f(b0);
  
  sgna0 = sgn(a0);
  sgnb0 = sgn(b0);
  
  mid = (a+b)/2;
  mid0 = f(mid);
  sgnmid0 = sgn(mid0);


  /* Here we will calculate new values for x until 
x(n) - x(n-1) is less than the desired accuracy, epsilon */

  while(fabs(b-a) > eps*fabs(b0-a0)){
    if(sgnmid0 == sgna0){
      printf("%lf\n",mid); //print the new value of midpoint to see process
      a = mid;             //since mid is on side of a, set a = mid
      mid = (a+b)/2;       //calculate new midpoint
      mid0 = f(mid);       //find new value at midpoint
      sgnmid0 = sgn(mid0);      //find new mid sign (pos or neg)
      printf("%d\n",sgnmid0);   //print out to see process...
      
    }else if(sgnmid0 == sgnb0){
      printf("%lf\n",mid);
      b = mid;
      mid = (a+b)/2;
      mid0 = f(mid);
      sgnmid0 = sgn(mid0);
      printf("%d\n",sgnmid0);
      
    }else{
      printf("Error\n");
    }
  }
  
  printf("There's a root at x = %lf.\n",mid);
  return(0);
}


double f(double x){
  double g;
  g = 5*x*x + 9*x - 80;
  return(g);
}

int sgn(double y){
  if(y > 0){
    return(1);
  }else{
    return(-1);
  }
}
