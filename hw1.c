#include <stdio.h>
#include <math.h>

//1.2 Velocity with Gravity//
/*

int main()
{
  double V,Vo,tf;
  double g = -9.8;
  int ni;

  printf("\nPlease enter the initial velocity, Vo [m/s],\nand final time, tf [s], separated by a comma.\n>");
  ni = scanf("%lf,%lf",&Vo,&tf);
  V = Vo + g*tf;
  printf("\nThe final velocity is %f m/s.\n",V);
}
*/


//1.4 Coulomb's Law//

/*
int main()
{
*/


//2.1 Velocity with Gravity and WHILE LOOP//

/*
int main()
{
  double V,Vo,t;
  double g = -9.8;
  int ni;

  printf("\nPlease enter the initial velocity, Vo [m/s]\n\n>Vo = ");
  ni = scanf("%lf",&Vo);
  while(t <= 100){
    V = Vo + g*t;
    printf("V=%5.1f m/s at time=%2.f seconds\n",V,t);
    t += 5;
  }
}
*/

//2.3 Parametric Equations (while)//

/*
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
*/


//2.4 Parametric Equations (for)//

/*
int main(){
  double x,y,t,n;
  t = 0;
  printf("\n( x , y )\n");
  for(n=0;n<=10;n++){
    x = 5.0 + 0.12*t*t;
    y = 0.02*t*t*t;
    printf("( %3.2f , %3.2f )\n",x,y);
    t = t + 0.5;
  }
}
*/
