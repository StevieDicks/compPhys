/* Newton-Raphson method #2 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double N(double x, double No);
double Nprime(double x, double No);

int main()
{
  double No;
  double N0;
  double x, x0=0;
  int ni;
  FILE *out,*rsp;
  char outfile[80];

  double eps = 1E-6;
  
  
  /* 
Print to GNUplot:
where No = 100.0
  */


  printf("\nEnter the name of the OUTPUT FILE \n(this will plot the atom count, N,\nversus time with an initial count of No = 100)\n > ");
  ni = scanf("%s",outfile);
  
  if((out = fopen(outfile,"w")) == NULL)
    {
      printf("\nCannot open %s for writing\n",outfile);
      exit(1);
    }

  for(x=0; x<=15; x=x+.1)
    {
      N0 = N(x,100);
      fprintf(out,"%3.1lf, %7.4lf\n",x,N0);
    }

  fclose(out);

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


  /*
Newton-Raphson portion!
  */ 

  //****** I would really like to implement a feature here that kicks the user if they do not put a value within the range! but, I wasn't sure how best to do this.******//
  
  printf("Please input a value for initial time, t, and initial atom count, No, to find t at N = No:\n   t,No\n > ");
  ni = scanf("%lf,%lf",&x,&No);
	     
  while(fabs(x0-x) > eps)
    {
      x0 = x;
      x = x - (N(x,No) - No/2)/Nprime(x,No);
      /*It is nu(x1) - nu0 b/c it is not accounting
for the fact that nu0 is not centered around zero--
it is centered around 20.1 (for this example).
Subtracting nu0 centers it around zero.
      */
    }

  printf("Newton-Raphson estimate = %lf.\n\n",x);
  return(0);
}
/////////////////////////////
double N(double x, double No)
{
  double N;
  double tau1 = 5.697, tau2 = 9.446;
  N = (No/2) * (exp(-x/tau1) + exp(-x/tau2));

  return(N);
}

//////////////////////////////////
double Nprime(double x, double No)
{
  double Nprime;
  double tau1 = 5.697, tau2 = 9.446;
  Nprime = (No/2) * ((-1/tau1)*exp(-x/tau1) + (-1/tau2)*exp(-x/tau2));

  return(Nprime);
}
