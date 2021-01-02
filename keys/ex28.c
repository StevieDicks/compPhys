/* Key for Ex 2.8:  The user is asked to guess the "key" and is continually
   prompted until success.  The user can get out by entering 0.  Note: the
   key in this example is a double.  Making it an integer would be easier
   on the user. */
#include <stdio.h>

int main()
{
  const double key = 134.5;
  double guess = 15.0;

  printf("\nEnter 0 to terminate the program\n");

  while(guess != key) {
    printf("\nEnter your guess (0 to terminate) > ");
    scanf("%lf",&guess);
    if(guess == 0.0) break;
    if(guess > key) printf("\nYour guess is too high");
    if(guess < key) printf("\nYour guess is too low");
    if(guess == key) printf("\nYour guess is correct!!!\n");
  }
  return(0);
}

