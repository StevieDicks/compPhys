#include <stdio.h>
#include <math.h>

int main(){
  double t,m,g,b,v;
  double vterm;

  g = 9.8;
  t = 0.0;
  v = 0.0;

  printf("\nPlease enter mass and air resistance, m and b, as such: m,b > ");
  scanf("%lf,%lf",&m,&b);

  vterm = -m * g / b; //calculate terminal velocity

  while(t <= 100 && fabs(v - vterm) > .000001){  //calculate v until t=100 or v=terminal velocity
    v = -(m * g / b)*(1 - exp(-b * t / m));
    printf("\nt = %3.1f v = %f",t,v);
    t++;
  }
  
  printf("\n");
  return(0);
}
