#include <stdio.h>    // printf
#include <stdlib.h>   // atoi
#include <time.h>

#include "timing.h"

#define N 1048576   // default length of array: 1<<20, or a 'mega', or 2^20 integers
                    // cannot be much larger than this in our codio VM
                    
#define STRIDE 1    // default stride (see sumvec_stride below)

/*
 * Stride-1 sum of all elements in the array V.
 */
int sumvec(int * v, int length) {  	
    int i, sum = 0; 

    for (i = 0; i < length; i++) {
        sum += v[i];
    }
    return sum;	
}

/*
 * Given an array v whose length is indicated by the parameter called length 
 * and a stride, access all elements in the array
 * by skipping past stride values each time. This is done by starting
 * at element zero, then element stride, then stride*2, etc., then
 * looping back around to element 1, then stride+1, then (stride+1)*2. etc.
 * The looping back to the beginning happens stride times, so that
 * all elements are eventually accessed.
 */

int sumvec_stride(int *v, int stride, int length) {  	
    int i, s, sum = 0; 

    for (s = 0; s < stride; s++) {  
        for (i = s; i < length; i=i+stride) { 
               sum += v[i];
        }
    }
    printf("\n");
    return sum;	
}


int main(int argc, char *argv[]) {
    // one argument for the size of stride to try
    int array_length = N;   // default if nothing entered on command line
    int stride = STRIDE;
    
    // argc is the total number of arguments, including the invoking of the program
    // argv[] is an array of strings
    // argv[0] always has the name of the program
    // argv[1] has the first argument typed
    // argv[2] has the second argument typed
    //
    
    if (argc >1) {
        array_length = atoi(argv[1]);  // 
    }
    
    if (argc > 2) {  // if we have provided a stride
          stride = atoi(argv[2]);    // atoi converts a string to an int
    }
    
    printf("For program %s, array length is set to %d and stride is set to %d\n", 
           argv[0], array_length, stride);
    
    // array to use. 
    // Note that we did not use malloc here- you could change it to do so for practice
    int vector[array_length];      // vector array to hold data values

    // other variables
    int i;
    int sum = 0;
        
    //////////////  need for timing code
    wallclock_t  t;       // from "timing.h", holds time data
    double  s;            // seconds
    ///////////////////////

    // initialize our vector of data, vector
    for (i = 0; i < array_length; i++) {
        vector[i] = ((i%2 == 0) ? 1 : -1);
    }

    //  sum each element with stride 1
//     /*
    wallclock_mark(&t);       // start timing
    sum = sumvec(vector, array_length);
    s = wallclock_since(&t);  // finish timing
    
    //should sum to zero 
    printf("stride 1: sum=%d\n", sum);
    printf("That took %.9f seconds wall clock time.\n", s);
//     */
    
    // now try with a particular stride
//     /*
    wallclock_mark(&t);       // start timing
    sum = sumvec_stride(vector, stride, array_length);
    s = wallclock_since(&t);  // finish timing
    
    //should sum to zero
    printf("stride of %d: sum=%d\n", stride, sum);
    printf("That took %.9f seconds wall clock time.\n", s);
//     */
     
    exit(0);
}
