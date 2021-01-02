/* Key for Ex 3.2: Passing a parameter by value */
#include <stdio.h>
void doit(double T);

int main()
{
  double T = 100.0;

  printf("\nMain before: T = %5.1f\n",T);

  doit(T);

  printf("\nMain after: T = %5.1f\n",T);

  return(0);
}

void doit(double T)
{

  T *= 2.5;
  printf("\nDoit: T = %5.1f\n",T);

  return;
}
