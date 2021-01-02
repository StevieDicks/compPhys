//Exam 2, problem 1

/*
Took most of code form ex47.c!...
This is why the notation may seem strange (like using N for pressure, etc...)
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double interp(double N, double T); //Tn = T [C]; Ne = Pressure [mPa]


int main()
{
  double T, N;
  //double dN;
  int ni;
  double Enthalpy;

  printf("\n\nPlease enter Pressure of environment and the temperature(in Celcius):\n\n(0.01-0.40),(150-1000)\n  P[mPa],  T[C]  > ");
  ni = scanf("%lf,%lf",&N,&T);
  //N for Pressure
  //T for Temp

  while(N < 0.01 || N > 0.40 || T < 150 || T > 1000){
    printf("\nThis value is out of the range.\nPlease enter new values:\n P[mPa],  T[C]  > ");
    scanf("%lf,%lf",&N,&T);
  }

  
  Enthalpy = interp(N,T);   //call interpolation function

  printf("\nEnthalpy for Superheated Water = %4.1lf\n\n",Enthalpy);
  
  return(0);
}

double interp(double N, double T) //copied from ex47.c
{
  double y1,y2,y3,y4;
  double t;
  double u;
  int i,j,n;
  double y;
  
  double H[11][6] = {
    {2783.0, 2780.2, 2776.6, 2769.1, 2761.2, 2752.8},
    {2879.6, 2877.8, 2875.5, 2870.7, 2865.9, 2860.9},
    {2977.5, 2976.2, 2974.5, 2971.2, 2967.9, 2964.5},
    {3076.7, 3075.8, 3074.5, 3072.1, 3069.9, 3067.1},
    {3280.0, 3279.3, 3278.6, 3277.0, 3275.5, 3273.9},
    {3489.7, 3489.3, 3488.7, 3487.7, 3486.6, 3485.5},
    {3706.3, 3706.0, 3705.6, 3704.8, 3704.0, 3703.3},
    {3929.9, 3929.7, 3929.4, 3928.8, 3928.2, 3927.6},
    {4160.6, 4160.4, 4160.2, 4159.8, 4159.3, 4158.9},
    {4398.3, 4398.2, 4398.0, 4397.7, 4397.3, 4396.9},
    {4642.8, 4642.7, 4642.6, 4642.3, 4642.0, 4641.7},
  };

  double Tn[11] = {150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000};
  double Ne[6] = {0.01, 0.05, 0.10, 0.20, 0.30, 0.40};

  i=0;
  for(n=0;n<6;n++) {
    if(Ne[n] <= N && Ne[n+1] >= N) {
      i=n;
      break;
    }
  }
  
  j=0;
  for(n=0;n<11;n++) {
    if(Tn[n] <= T && Tn[n+1] >= T) {
      j=n;
      break;
    }
  }
  
  y1 = H[j][i];
  y2 = H[j][i+1];
  y3 = H[j+1][i+1];
  y4 = H[j+1][i];


  t = (N - Ne[i])/(Ne[i+1] - Ne[i]);
  u = (T - Tn[j])/(Tn[j+1] - Tn[j]);

  y = (1-t)*(1-u)*y1 + t*(1-u)*y2 + t*u*y3 + (1-t)*u*y4;
  return(y);
}
