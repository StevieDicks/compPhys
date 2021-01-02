/* Computes the h(t) using Fourier Series
- The value of M is the number of coefficients to compute
- Here, h(t)= -1 (for -pi<t<0) and +1 (for 0<t<pi), 0 otherwise
- C Thaxton, PHY4020/5020 
Modified for Ex 10.2 R.O. Gray */

#include <stdio.h>
#include <math.h>
#include "comphys.c"
#include "comphys.h"
#define pi 3.141592653589793

float trap(float l,float u,int m,int N); // Use trapezoidal method
float integrand(float x, int m); // This is the integrand of the bms
float w=1.0; //omega (here - w-2pi/Period where Period=2pi)
int main()
{
   FILE *out;
   int m; // Index of the b coefficients
   int M=50; // Number of coeeficients to compute - **change this**
   int T=201;  // Number of time steps (200 is sufficient to resolve)
   int t; // This is a counter to keep track of the h(t) function to plot
   float *b,*h;
   double ll,ul,j,dj;
   float fac;
   b=vector(0,M);  // coefficients
   h=vector(1,T);  // function built from Fourier terms
   ll=-pi;  // lower time limit
   ul=pi;   // upper time limit

// Prepare to write for plotting
   printf("\nBrute force complex Fourier transform algorithm");
   if ((out=fopen("ex102.out","w"))==NULL) {
      printf("\nCannot open file for output\n");
      getchar();
      return(0);  		
   }

// Loop through the wave numbers    
   for (m=0;m<=M;m++)
   {
     if(m == 0) fac = 0.5; /* Note factor for a0 in Eq 10.6 */
     else fac = 1.0; 
      b[m]=fac*(1.0/pi)*trap(ll,ul,m,T);
      printf("\nb[%d]=%f",m,b[m]);

// Build the h(t) function as we go
      t=0;
      dj=(ul-ll)/(float)T;
      for (j=ll;j<=ul;j+=dj)
      {
         t++;
         h[t]+=b[m]*cos((double)m*w*j);
      }
   }

// Write out for plotting
   t=0;
   for (j=ll;j<=ul;j+=dj)
   {
      t++;
      fprintf(out,"%f %f\n",j,h[t]);
   }
   fclose(out);
   printf("\nProgram complete without known error.\n");
   return(1);
}

float trap (float l, float u, int m, int N)

{
   float x,integral,dx;
   int i;

   if (u==l) return (0.0);
   dx=(u-l)/(float)(N-1);

   integral=0.0;
   integral+=0.5*(integrand(u,m)-integrand(l,m));
   x=l+dx;
   for (i=1;i<N;i++)
   {
       integral += integrand(x,m);
       x+=dx;
   }
   integral*=dx;
   return(integral);
}

float integrand(float x, int m)
{
   if (x<0) return ((1.0+x/pi)*cos((float)m*w*x));
   return((1.0-x/pi)*cos((float)m*w*x));
}

