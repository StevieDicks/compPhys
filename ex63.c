#include <stdio.h>
#include <stdlib.h>
#include "comphys.c"
#include "comphys.h"

int main()
{
  float J;
  float x;
  float a, b, c;
  int ni;
  FILE *out,*rsp;
  char outfile[80];
  
  printf("This program will plot the Bessel function J0 from t = 0 to 15\nEnter the name of the OUTPUT FILE\n > ");
  ni = scanf("%s",outfile);
  
  if((out = fopen(outfile,"w")) == NULL)
    {
      printf("\nCannot open %s for writing\n",outfile);
      exit(1);
    }

  for(x=0; x<=15; x=x+.1)
    {
      J = bessj0(x);
      fprintf(out,"%3.4f, %7.4f\n",x,J);
    }

  fclose(out);


  
  /* print to GNUplot */
  
  if((rsp = fopen("gnuplot.rsp","w")) == NULL)
    {
      printf("\nCannot open gnuplot.rsp for writing\n");
      exit(1);
    }
  fprintf(rsp,"set xrange[0:15]\n");
  fprintf(rsp,"plot '%s' using 1:2 with lines\n",outfile);
  fprintf(rsp,"pause mouse\n");
  fprintf(rsp,"replot\n");
  fclose(rsp);
  if(system("gnuplot gnuplot.rsp") == -1)
    {
      printf("\nCommand could not be executed\n");
      exit(1);
    }


  
  /* Now bracket bessj0 to find the x-value for the minimum */
  // note: this section will reuse "x"


  printf("Please enter values for a, b, and c, \nthe left hand, middle, and right hand start-points for the interpolation.\n a, b, c > ");
  ni = scanf("%f, %f, %f",&a,&b,&c);

  while(fabs(a-c) > 1E-5)
    {
      if(fabs(b-a) > fabs(c-b))
	{
	  x = (a+b)/2;
	  if(bessj0(x) > bessj0(b)) //then the interval is (x,b,c)
	    {
	      b = x;
	      printf("%f\n",x);
	    }
	  else //the interval is (a,x,b)
	    {
	      c = b;
	      b = x;
	      printf("%f\n",x);
	    }
	}
      else
	{
	  x = (b+c)/2;
	  if(bessj0(x) > bessj0(b)) //then the interval is (a,b,x)
	    {
	      c = x;
	      printf("%f\n",x);
	    }
	  else //the interval ix (b,x,c)
	    {
	      a = b;
	      b = x;
	      printf("%f\n",x);
	    }
	}
    }
  printf("The minimum is: x = %f, at %f\n",x,bessj0(x));
  return(0);
}
