#include <stdio.h>
#include <stdlib.h>
#include <math.h>

  /*
This program is designed to take the Lagrangian interpolation of two vectors,
xn and yn, and interpolate a function between them. The Lagrangian is a function
so it can calculate and return multiple answers, like L(x1), L(x2), etc.
Otherwise, this program works just like a normal bisecting program.
  */

double L(double x);
int sgn(double y);

int main()
{
  double a = 6.4, b = 7.3, A, B, mid;
  int sgnmid,sgna,sgnb;
  double eps = 1E-6;

  B = b;
  A = a;

  while(fabs(b-a) > eps*fabs(B-A))
    {
      mid = (a+b)/2;
      sgnmid = sgn(mid);
      sgna = sgn(a);
      sgnb = sgn(b);
      //printf("%d,%lf\n",sgnmid,mid);  //to see process
      if(sgnmid == sgna)
	{
	  a = mid;
	}
      else if(sgnmid == sgnb)
	{
	  b = mid;
	}
      else
	{
	  printf("Error\n");
	}
    }
  
  printf("Radius of surface =  %lf.\n",mid);
}

////////////////////////////////////////////////////////////////////////////////////

double L(double x)
{
  double L=0.0;
  int i;
  int j=0;
  //int n;
  double x1,x2,x3,x4;
  double y1,y2,y3,y4;
  double term1,term2,term3,term4;

  double xn[10] = {6.4, 6.5, 6.6, 6.7, 6.8, 6.9, 7.0, 7.1, 7.2, 7.3};
  double yn[10] = {0.022718, 0.017866, 0.013162, 0.008598, 0.004168, -0.000134, -0.004312, -0.008373, -0.012321, -0.016161};

  for(i=0;i<10;i++)
    {
      if(xn[i] < x && xn[i+1] >= x)
	{
	  j=i;
	  break;
	}
    }

  if(j==0)
    {
      j = j+1;
    }
  else if(j==34)
    {
      j = j-1;
    }

  
  x1 = xn[j-1];
  x2 = xn[j];
  x3 = xn[j+1];
  x4 = xn[j+2];
  
  y1 = yn[j-1];
  y2 = yn[j];
  y3 = yn[j+1];
  y4 = yn[j+2];

  term1 = y1*((x-x2)*(x-x3)*(x-x4))/((x1-x2)*(x1-x3)*(x1-x4));
  term2 = y2*((x-x1)*(x-x3)*(x-x4))/((x2-x1)*(x2-x3)*(x2-x4));
  term3 = y3*((x-x1)*(x-x2)*(x-x4))/((x3-x1)*(x3-x2)*(x3-x4));
  term4 = y4*((x-x1)*(x-x2)*(x-x3))/((x4-x1)*(x4-x2)*(x4-x3));

  L = term1 + term2 + term3 + term4;
  
  return(L);
}

////////////////////////////////////////////////////////////////////////////////////
int sgn(double y)
{
  if(L(y) > 0)
    {
      return(1);
    }
  else
    {
      return(-1);
    }
}
