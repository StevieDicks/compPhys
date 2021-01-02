#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "comphys.h"
#include "comphys.c"

/*
void correl(float data1[], float data2[], unsigned long n, float ans[]);

data1/data2[] = the data sets, which will be read in
n is number of data points, subdivision (128 here)
respns[] = exp(-t/RC)
m is number of points of response function
isign = +1 for convolution, -1 for deconvolution
ans[] is predefined array to store answer
*/

int main() {
