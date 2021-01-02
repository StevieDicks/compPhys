//sort_demo
#include <stdio.h>
#include "comphys.h"
#include "comphys.c"

int main() 
{
	int a[9]={7,12,1,-2,0,15,4,11,9};
        int a0[9];
	int i=0;

        for (i=0;i<=8;i++) a0[i]=a[i];

	qsint(a,0,8);
        printf("\nQuicksort demo:\n");
	printf("\nOriginal    Sorted\n");
	for(i = 0; i < 9; ++i)
		printf("   %3d       %3d\n",a0[i],a[i]);
        return(0);
}
