#include <stdio.h>
#include <stdlib.h>

int main(){
  long int a,b;
  long int ni;
  int m=0;
  int n=0;
  a = 42;
  printf("\nGuess the number.\n>");
  ni = scanf("%ld",&b);
  while(1){ 
  if(b<a){
    if(m==3)printf("Higher Please\n>");
    else printf("Higher!\n>");
    ni = scanf("%ld",&b);
    m++;
  }else if(b>a){
    if(n==3)printf("Lower Please\n>");
    else printf("Lower...\n>");
    ni = scanf("%ld",&b);
    n++;
  }else{printf("\nYou got it! It's %ld! You must be a physicist.\n",a);
    break;
  } 
  }
}
