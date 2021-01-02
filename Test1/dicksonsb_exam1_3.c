/* Ising Model */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "comphys.c"
#include "comphys.h"

double ising(float x);

int main(){
  int i;
  int *arbvector;


  //RANDOM//
  long idum = -1;
  time_t now;
  float x, rn;
  
  now = time (NULL);

  idum = -1*now;

  rn = ran1(&idum);
  //END RANDOM//
  
  arbvector = ivector(0,9);

  for(i=0; i<10; i++){
    x = ran1(&idum);
    arbvector[i] = ising(x);
    printf("%d,",arbvector[i]);
  }

  printf("\n");
  
  return(0);
}

double ising(float x){
  int L;

  if(x <= .5){
    L = -1;
  }else{
    L = 1;
  }
  return(L);
}
