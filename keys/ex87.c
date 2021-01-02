/* Ex 8.7 R.O. Gray: integration of Emden's equation using the Adams-
   Bashforth-Moulton predictor-corrector routine */ 

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define n 3

double y(double x);
double yp(double x);
double zp(double x);
double ypp(double x,double y,double z);

int main() 
{ 
   double xm2,xm1,x0,x1;
   double ym2,ym1,y0,y1;
   double zm2,zm1,z0,z1;       
   double zpm2,zpm1,zp0,zp1;   
   double dx=0.01;
   double m,b,xs; 
   FILE *out;
   
/* Prime the Pump! */
   ym2 = y(0.0);
   zm2 = yp(0.0);
   zpm2 = zp(0.0);
   ym1 = y(dx);
   zm1 = yp(dx);
   zpm1 = zp(dx);
   y0 = y(2.0*dx);
   z0 = yp(2.0*dx);
   zp0 = zp(2.0*dx);
   xm2 = 0.0;
   xm1 = dx;
   x0 = 2.0*dx;
   x1 = 3.0*dx;

   if ((out=fopen("ex87.out","w"))==NULL) {
      printf("\nCannot open file for output\n");
      exit(1);
   }

   fprintf(out,"%3.1f   %8.6f   %8.6f\n",xm2,ym2,zm2);
   fprintf(out,"%3.1f   %8.6f   %8.6f\n",xm1,ym1,zm1);
   fprintf(out,"%3.1f   %8.6f   %8.6f\n",x0,y0,z0);
    
   /* Implementation of two interleaved A-B-M systems */
  
   y1 = y0;

   while(y1 >= 0.0)
   {
      /* Predictor Step */
      z1 = z0+(23.0*zp0-16.0*zpm1+5.0*zpm2)*dx/12.0;  
      y1 = y0+(23.0*z0-16.0*zm1+5.0*zm2)*dx/12.0;     

      /* Calculate zp1=ypp */
      zp1 = ypp(x1,y1,z1);

      /* Corrector Step */
      z1 = z0+(5.0*zp1+8.0*zp0-zpm1)*dx/12.0; 
      y1 = y0+(5.0*z1+8.0*z0-zm1)*dx/12.0; 

      /* Recalculate zp1=ypp - this step is optional! */
      zp1 = ypp(x1,y1,z1);
      fprintf(out,"%5.3f   %8.6f   %8.6f\n",x1,y1,z1);

      if(y1 <= 0.0) break;

      /* Update variables */
      xm2 += dx;
      xm1 += dx;
      x0 += dx;
      x1 += dx;
      ym2 = ym1;
      ym1 = y0;
      y0 = y1;
      zm2 = zm1;
      zm1 = z0;
      z0 = z1; 
      zpm2 = zpm1;
      zpm1 = zp0;
      zp0 = zp1; 
   }            

   /* interpolate to find the value of x where y = 0 (stellar surface) */
   m = (y1-y0)/(x1-x0);
   b = y1 - m*x1;

   xs = -b/m;

   printf("\nThe surface occurs at x = %f\n",xs);

   fclose(out);        
   return(0);
} 

double y(double x) 
{
   return (1-(x*x)/6.0+(double)n*pow(x,4)/120.0-(5.0*(double)n-8.0*(double)(n*n))*pow(x,6)/15120.0);
}

double yp(double x) 
{
   return (-2*x/6.0+4.0*(double)n*pow(x,3)/120.0-6.0*(5.0*(double)n-8.0*(double)(n*n))*pow(x,5)/15120.0);
}

double ypp(double x, double y, double z) 
{
   return (-pow(y,n)-(2/x)*z);
}

double zp(double x) 
{
   return (-(1.0/3.0)+12.0*(double)n*pow(x,2)/120.0-30.0*(5.0*(double)n-8.0*(double)(n*n))*pow(x,4)/15120.0);
}

