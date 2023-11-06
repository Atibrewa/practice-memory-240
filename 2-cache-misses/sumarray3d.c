#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "timing.h"

#define N 1<<8

// global variable 
// (not typically a good idea, but avoids having
// the array on the stack)
int a[N][N][N];

/* 
 * sumarray3d uses 3d row-major ordering to
 * access all the elements of a and sum them together.
 */
int sumarray3d(int a[N][N][N]) {  	
    int i, j, k, sum = 0;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                sum += a[i][j][k];
            }
        }
    }
    return sum;	
}


/*
 * Example of array access that has poor locality.
 * TODO: you implement a loop access that exhibits poor locality
 *       add timing of it to main.
 */
int sumarray3d_slower(int a[N][N][N]) {  	
    int i, j, k, sum = 0;

    // implement a case where the locality is not as good
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                sum += a[k][i][j];
            }
        }
    }
    
    return sum;
    
}


int main(int argc, char *argv[]) {

   // These next several values are for collecting command-line arguments
    extern char *optarg;
    extern int optind, optopt;
    int slow = 0;    // default is to run the faster, 
    int fast = 1;    //     cache-friendly version
    int errflg;
   
    int c;
  
    /////////////////////////////////////////////////////////////
    //get the arguments
    //  looking for -s for slower version
    //  
    while ((c = getopt (argc, argv, "s")) != -1) {
        
        switch (c)
          {
          case 's':
            slow = 1;
            fast = 0;
            break;
        case '?':
            printf("unknown arg %c\n", optopt);
            break;
        }
              
    }
  
  
    int i, j, k;

    // initialize
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                a[i][j][k] = ((k%2 == 0) ? 1 : -1);
            }
        }
    }

    wallclock_t  t;    // from "timing.h", for holding times
    double  s;         // seconds
    
    if (fast) {
      wallclock_mark(&t);       // start timing
      int sum = sumarray3d(a);
      s = wallclock_since(&t);  // finish timing

      /* should return zero */
      printf("sum=%d\n", sum);
      printf("Fast version took %.9f seconds wall clock time.\n", s);
    } else {
      wallclock_mark(&t);       // start timing
      int sum = sumarray3d_slower(a);
      s = wallclock_since(&t);  // finish timing

      /* should return zero */
      printf("sum=%d\n", sum);
      printf("Slow version took %.9f seconds wall clock time.\n", s);
    }
    
    
    exit(0);
}
