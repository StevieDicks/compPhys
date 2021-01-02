#include "comphys.c"
#include "comphys.h"
#include <stdio.h>



int main()
{
  float grain0[50];
  float grain[50];
  int i, ni;
  float a;
  float A,b,c,d,e,f,g,h,I,j;
  float ave = 0;
  float SD = 0;
  float sum1 = 0;
  
  fopen("grains.dat","r");
  for(i=0;i<50;i++){
    ni = scanf("%f",&grain[i]);
    if(grain[i] >= 1.00 && grain[i] <=1.10){
      A++;
    }else if(grain[i] > 1.10 && grain[i] <=1.20){
      b++;
    }else if(grain[i] > 1.20 && grain[i] <=1.30){
      c++;
    }else if(grain[i] > 1.30 && grain[i] <=1.40){
      d++;
    }else if(grain[i] > 1.40 && grain[i] <=1.50){
      e++;
    }else if(grain[i] > 1.50 && grain[i] <=1.60){
      f++;
    }else if(grain[i] > 1.60 && grain[i] <=1.70){
      g++;
    }else if(grain[i] > 1.70 && grain[i] <=1.80){
      h++;
    }else if(grain[i] > 1.80 && grain[i] <=1.90){
      I++;
    }else{
      j++;
    }
  }
      

  for(i=0;i<50;i++) grain0[i] = grain[i]; //making the original string

  for(i=0;i<50;i++){
    ave = ave + grain0[i]; //calculating average grain size
  }
  ave = ave/50;

  for(i=0;i<50;i++){
    sum1 = sum1 + 1*pow((grain[i]-ave),2);
  }
  SD = sqrt(sum1 / 50);

  qsint(grain,0,49);
  printf("\nSorting grains:\n");
  printf("\nOriginal      Sorted\n");
  for(i=0; i<50; i++)
    printf("%1.2f       %1.2f\n",grain0[i],grain[i]);
  printf("\n\nGrain distribution by bins:\n\n");
  printf("1.0 < Grains <= 1.1: %g\n\n1.1 < Grains <= 1.2: %g\n\n1.2 < Grains <= 1.3: %g\n\n1.3 < Grains <= 1.4: %g\n\n1.4 < Grains <= 1.5: %g\n\n1.5 < Grains <= 1.6: %g\n\n1.6 < Grains <= 1.7: %g\n\n1.7 < Grains <= 1.8: %g\n\n1.8 < Grains <= 1.9: %g\n\n1.9 < Grains <= 2.0: %g\n\n",A,b,c,d,e,f,g,h,I,j);

  printf("\nThe average grain size is %1.2fmm\n",ave);
  printf("The standard deviation of the size distribution is %1.2gmm\n\n",SD);

  return(0);
}
