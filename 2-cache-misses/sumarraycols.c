#include <stdio.h>
#include <stdlib.h>

#include "timing.h"

// square matrix
#define M (1<<13)   // 8192 x 8192
#define N M

// global variable 
// (not typically a good idea, but avoids having
// the array on the stack)
int a[M][N];

/* $begin sumarraycols */
int sumarraycols(int a[M][N]) 
{  	
    int i, j, sum = 0;

    for (j = 0; j < N; j++) {
        for (i = 0; i < M; i++) {
            sum += a[i][j];
        }
    }
    
    return sum;	
}
/* $end sumarraycols */


int main()
{
    //////////////  need for timing code
    wallclock_t  t;
    double  s;
    ///////////////////////
    
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            a[i][j] = ((j%2 == 0) ? 1 : -1);
        }
    }

    wallclock_mark(&t);       // start timing
    /* should sum to zero */
    int sum = sumarraycols(a);
    s = wallclock_since(&t);  // finish timing
    
    printf("sum=%d\n", sum);
    printf("That took %.9f seconds wall clock time.\n", s);
    
    exit(0);
}
