/* Key to Prob 1, Exam 2, 2016.  2-D interpolation in a table of Enthalpies */
#include <stdio.h>
#include <stdio.h>
#include <math.h>

int main()
{
  double H[11][6] = {{2783.0, 2780.2, 2776.6, 2769.1, 2761.2, 2752.8},
		     {2879.6, 2877.8, 2875.5, 2870.7, 2865.9, 2860.9},
		     {2977.5, 2976.2, 2974.5, 2971.2, 2967.9, 2964.5},
		     {3076.7, 3075.8, 3074.5, 3072.1, 3069.9, 3067.1},
		     {3280.0, 3279.3, 3278.6, 3277.0, 3275.5, 3273.9},
		     {3489.7, 3489.3, 3488.7, 3487.7, 3486.6, 3485.5},
		     {3706.3, 3706.0, 3705.6, 3704.8, 3704.0, 3703.3},
		     {3929.9, 3929.7, 3929.4, 3928.8, 3928.2, 3927.6},
		     {4160.6, 4160.4, 4160.2, 4159.8, 4159.3, 4158.9},
		     {4398.3, 4398.2, 4398.0, 4397.7, 4397.3, 4396.9},
		     {4642.8, 4642.7, 4642.6, 4642.3, 4642.0, 4641.7}};
  double p[6] = {0.01,0.05,0.10,0.20,0.30,0.40};
  double te[11] = {150,200,250,300,400,500,600,700,800,900,1000};
  double t,u,T,P;
  double y1,y2,y3,y4,E;
  int ni,i,j,k;

  T = 0.0;
  while(T < 150.0 || T > 1000) {
    printf("Enter a temperature between 150 and 1000 C > ");
    ni = scanf("%lf",&T);
  }
  P = 0.0;
  while(P < 0.01 || P > 0.40) {
    printf("Enter a pressure between 0.01 and 0.40 MPa > ");
    ni = scanf("%lf",&P);
  }


  // Bracket in 2-D
  for(i=0;i<10;i++) {
    if(T >= te[i] && T <= te[i+1]) {
      j = i;
      break;
    }
  }

  for(i=0;i<5;i++) {
    if(P >= p[i] && P <= p[i+1]) {
       k = i;
       break;
    }
  }

  printf("j = %d k = %d\n",j,k);

  // Interpolation formulae
  t = (T - te[j])/(te[j+1]-te[j]);
  u = (P - p[k])/(p[k+1]-p[k]);

  y1 = H[j][k];
  y2 = H[j+1][k];
  y3 = H[j+1][k+1];
  y4 = H[j][k+1];

  E = (1-t)*(1-u)*y1 + t*(1-u)*y2 + t*u*y3 + (1-t)*u*y4;

  printf("Enthalpy at the selected point is %6.1f\n",E);

  return(0);
}


