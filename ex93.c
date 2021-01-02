#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "comphys.c"
#include "comphys.h"

//void gaussj(float **a, int n, float **b, int m); //this program (from comphys.c) takes the inverse of a matrix "a" and multiplies it by "b".

int main(){
  float **a, **b;
  int i,j;

  //set matrix sizes: nxn matrix a and nxm matrix b
  int n = 3;
  int m = 1;

  a = matrix(1,n,1,n);
  b = matrix(1,n,1,m);

  //fill in values of matrix
  a[1][1] = 1;
  a[1][2] = 5;
  a[1][3] = 3;
  a[2][1] = 2;
  a[2][2] = 1;
  a[2][3] = 9;
  a[3][1] = 3;
  a[3][2] = 8;
  a[3][3] = 8;
  
  b[1][1] = 5;
  b[2][1] = 2;
  b[3][1] = 1;

  //run gaussj function
  gaussj(a, n, b, m);

  //print the results in matrix form
  printf("\ninverse(a) = {\n");
  for(i=1;i<=3;i++) {
    printf("{");
    for(j=1;j<=3;j++) {
      printf(" %f ", a[i][j]);
    }
    printf("},\n");
  }
  printf("}\n");

  printf("\nx = {\n");
  for(i=1;i<=3;i++) {
    printf("{ %f },\n", b[i][1]);
  }
  printf("}\n\n");
  

  return(0);
}
