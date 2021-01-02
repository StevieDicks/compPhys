#include <stdio.h>
#include <math.h>

int main(){
  double x,y,t;
  t = 0;
  printf("\n( x , y )\n");
  while(t<=5.0){
    x = 5.0 + 0.12*t*t;
    y = 0.02*t*t*t;
    printf("( %3.2f , %3.2f )\n",x,y);
    t = t + 0.5;
  }
}
