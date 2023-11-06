# 1: Spatial and Temporal Locality

In this activity, you will observe good and bad locality using example code and timing functions. You will be asked questions as you complete this activity, which you should answer in a file called `responses.txt`. (Don't forget to `git add` this file!)

There are four code files, which are examples from section 6.5 in the text:


| File          | What it does           |
| ------------- |-------------|
| sumvec.c      | 1-d array manipulation with varying degrees of good and poor locality |
| sumarrayrows.c     | 2-d matrix manipulation with good locality      |
| sumarraycols.c | 2-d matrix manipulation with poor locality        |
| sumarray3d.c | 3-d matrix manipulation with varying degrees of good and poor locality       |

The task associated with each file is described below, after a note on how timing will work for this activity.

### Timing Code

You can observe the impact of poor localty by timing how long your code takes to execute. This is a skill you should use as you work on larger projects. You will use a helper file called `timing.h` for this purpose.

Files ending in .h are designed to be included in .c code files. So far, you have included library .h files, such as stdio.h, that are built into the language. In this case, you are using one as if it was written by you as a programmer. On many C software development teams, there are a certain core set of these .h files that are shared within the team for different reasons. One reason is that the file contains utility functions that are used routinely in a project. This `timing.h` file falls into this category.

You might time portions of code to determine how efficient they are and whether you should update them to improve run time. 

In `timing.h`, you have two functions and a typedef that allow you to time code more simply. Each of the four code files will include this file in this way:

    #include "timing.h"

Notice how a file we have written that is not a library .h file is included using the double quotes instead of < and >.

The basic concept behind using these functions is the following:

1. Mark a start time just before a section of code that you want to time.
2. Execute code to be timed.
3. Retrieve the amount of time that has passed since the mark at step 1.

## One-Dimensional Arrays: `sumvec.c`

Start by making and the executing *sumvec* with no command line arguments. This will run the program in its default configuration.

    ./sumvec

This code is creating an array of a given size and accessing it with a given stride. We can set the size N and stride S from the command line when running the program, like so:

    ./sumvec N S

Try running both variations several times, and with multiple values of N and S. 

Note that the code for 2 different functions is being timed: 

1. `sumvec`, a stride-1 loop of the array. 
2. `sumvec_stride`, which accesses the array in a special pattern when the value of the argument called **stride** is greater than 1. The default value of 1 establishes a baseline for how much time this function takes.

### Task: Determine the access pattern of `sumvec_stride`

Look carefully at the code for the function `sumvec_stride`. Work with your neighbors to describe and visualize how the elements in the array are being accessed when the stride is greater than 1.

* Why does it take longer to run `sumvec_stride` than `sumvec` when the stride length is 1?

Now change the stride by running the code like this:

    ./sumvec 1048576 4
    
Try running it several times, and consider using larger or smaller array lengths, as needed for your machine. Observe whether the code with this stride takes longer to run or not. Try it with larger strides, such as 8, 16, 32, and 64.

* What is happening as you run this code? What explains the running time of `sumvec_stride` as compared to the original `sumvec`?


### Challenge: Practice Timing

Add code to check how long it takes to initialize the 1-d array (in the middle of `main` where the loop is). This is also a stride-1 reference pattern.


## Two-Dimensional Arrays

Now you will observe access patterns of 2D arrays. You have 2 programs, each of which statically creates a 2D array, or matrix, of M rows and N columns. You start with M and N being equal, so that the matrix is square. The code files are called:

    sumarrayrows.c
    sumarraycols.c
    
Look at the .c files for each to determine the difference in their access patterns as they sum values in the array.

* Which of these do you expect to have better locality of reference when it comes to the array `a`, which is considered data?

* Will either of them have better locality of reference when considering the instructions being executed in main and the function called from main? Explain whether the locality will be good or bad for the instruction references.

### Run the code

1. Execute `sumarrayrows` several times to determine an approximate average time to execute the `sumarrayrows` function. 

2. Execute `sumarraycols` several times to determine an approximate average time to execute the `sumarraycols` function. 

* Which one runs faster and why?

### Challenge: Practice Timing

Add code to check how long it takes to initialize the 2-D array (at the beginning of `main` where the nested loop is). This is row-major order reference pattern in each case.

## Three-Dimensional Arrays

Open the file called `sumarray3d.c`.

The function `sumarray3d` in `summarray3d.c` should run about as fast as possible when accessing all the elements in the 3D array. Run it a few times to see how much time it takes to access the 3D array using the access pattern in the `sumarray3d` function.

### Task: Make it slower

Complete the function `sumarray3d_slower` by changing the access pattern to one that demonstrates poor locality. There are a few ways to do this--experiment with different possibilities. Time your slower function in `main`. Then make and run the code a few times to observe your slower access pattern.
