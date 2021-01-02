#include <stdio.h>
#include <math.h>

void doit();
double T = 100.0;

int main(){
  doit(&T);
  printf("\n%3.1f\n\n",T);
}

void doit(double *T){
  *T=*T*2.5;
  return;
}
