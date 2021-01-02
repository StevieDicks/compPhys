/* Key for Ex 3.3:  Passing a parameter as an external variable */
#include <stdio.h>
void doit();
double T;

int main()
{
  T = 100.0;

  printf("\nMain before: T = %5.1f\n",T);

  doit();

  printf("\nMain after: T = %5.1f\n",T);

  return(0);
}

void doit()
{

  T *= 2.5;
  printf("\nDoit: T = %5.1f\n",T);

  return;
}
