/*
 Multipe roots of an equation f(x)=0 in [a,b] interval
 Method: call Bisectional method for subintervals
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double root_mr(double(*)(double), double, double, double, double[], int, int&);
double fzero(double);

int main()
{
	const int intervals = 1000;         // number of subintervals to to look for roots
    double a,b,roots[intervals], eps;
    int i, nroots;
    cout.setf(ios::fixed | ios::showpoint);
    cout.precision(5);

    a = 1.0;                    // left endpoint
    b = 6.0;                    // right endpoint
    eps = 1.0e-6;               // desired uncertainity of the root

    root_mr(fzero, a ,b ,eps, roots, intervals ,nroots);
   
    cout << " root" << "      value"       << endl;    

    if (nroots == 0 ) cout << " no roots found" << endl;
    for (i = 1; i <= nroots; i = i+1)
    cout << setw(5) << i << setw(12) << roots[i-1] << endl;
    system ("pause");
    return 0;
}
/*
 *  Function f(x) for the equation f(x)=0
*/
    double fzero(double x)
{
    double y;
    y = sin(x*x)*cos(x+1.0)/(x*x+1.0);    
    return y;
}

/* Test output

 root      value
    1     1.77245
    2     2.50663
    3     3.06998
    4     3.54491
    5     3.71239
    6     3.96333
    7     4.34161
    8     4.68947
    9     5.01326
   10     5.31736
   11     5.60499
   12     5.87856

*/

    double root_mr(double(*f)(double), double a, double b, double eps, 
    double roots[], int intervals, int nroots)
/*
====================================================================
 Program to find multiple roots of an equation f(x)=0
 on an interval [a,b] using the Bisectional method for subintervals
 written by:    Alex Godunov
 Last revision: 31 January 2007 
--------------------------------------------------------------------
 input ...
 f   - function which evaluates f(x) for any x in the interval a,b
 a   - left endpoint of initial interval
 b   - right endpoint of initial interval
 eps - desired uncertainity of the root
 intervals - number of subintervals for [a,b]

 output ...
 roots  - roots of equation f(x)=0
 nroots - number of roots 

 Limitations: a function f(x) must change sign between a and b
 Max number of allowed iterations is 1000 (accuracy (b-a)/2**1000)
====================================================================
*/        
{
   double xl, x0, xr, dx;    
   int i, j, n, iter=1000;
   n = 0;                   // n is the counter for roots
   dx = (b-a)/intervals; 
//* start loop over subintervals
   j= 0;
   while (j < intervals)
   { j = j + 1;
	xl = a + (j-1)*dx;
    xr = xl + dx;
    if(f(xl)*f(xr) > 0.0) continue;
//** start bisectional loop over the subinterval j
    i = 0;
    while (fabs(xr - xl) >= eps)
    {
	  i = i + 1;
      x0 = (xr + xl)/2.0;
      if((f(xl) * f(x0)) <= 0.0 ) 
        xr = x0;
        else 
        xl = x0;
      if(i >= iter) break;   
    }
    if (i >= iter) continue;  //do not count roots when max. iterations exceeded
    roots[n] = x0;
    n = n+1;
   }
    nroots = n; 
    return 0;
} 
   

