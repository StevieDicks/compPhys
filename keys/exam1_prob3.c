//Key for Problem 3, Exam 1, Fall 2016.  R.O. Gray
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "comphys.h"
#include "comphys.c"
int ising(long *idum);

int main()
{
  int spin[10];
  int i;
  long idum = -1;
  time_t now;
  float rn;

  //Initialize the random number generator
  now = time(NULL);
  idum = -1*now;

  rn = ran1(&idum);

  //Call spin to create the list of 10 spins for the Ising model
  for(i=0;i<10;i++) spin[i] = ising(&idum);

  for(i=0;i<10;i++) printf("%d ",spin[i]);
  printf("\n");

  return(0);
}

// ising produces a random spin -- up or down, with equal probability
int ising(long *idum)
{
  float x;
  int n;
  //Notice how idum is used in ising
  x = ran1(idum);
  if(x < 0.5) n = -1;
  if(x >= 0.5) n = 1;

  return(n);
}
