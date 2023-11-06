# 2: Cache Misses

In this activity, you will examine cache misses resulting from real code. The provided code  is similar to the code that you observed in memory activity 1. Discuss each question with your table and write your answers in a new file called `responses.txt`. 

Build these files with make:

| File          | What it does           |
| ------------- |-------------|
| sumvec.c      | 1-d array manipulation with varying degrees of good and poor locality |
| sumarrayrows.c     | 2-d matrix manipulation with good locality      |
| sumarraycols.c | 2-d matrix manipulation with poor locality        |
| sumarray3d.c | 3-d matrix manipulation with varying degrees of good and poor locality       |

## One-Dimensional Array

The code for `sumvec.c` has been updated slightly. The function called `sumvec_stride` has been improved to ensure that it has exactly the same number of data accesses and nearly equal number of instructions. In addition, `main()` now has a slightly more sophisticated way of handling the command line arguments. The possible arguments that you can include are:

    -n followed by a number for the size of the array
    -s followed by a number for the size of the stride

This enables you to execute the program like these examples:

    ./sumvec -n 1048576 -s 1
    ./sumvec -n 1048576 -s 4
    ./sumvec -n 1048576 -s 8
    ./sumvec -n 1048576 -s 16
    ./sumvec -n 1048576 -s 32

You can try bigger numbers for the size of the array, like this:

    ./sumvec -n 2048576 -s 4
    
### Determine Actual Cache Misses

You will be using **valgrind** and its accompanying utility **cachegrind** in
order to track cache misses in this code. 

You run valgrind with its cachegrind tool like this:

    valgrind --tool=cachegrind ./sumvec -n 1048576 -s 1

This will show the number of cache misses in the *D* caches, which hold the data array used in this code, for the best case: stride-1. 

* What is the miss rate reported for the D1 cache?

You can also observe instructions misses by checking the miss rate for the I1 cache.

Now try running it again with various values of stride greater than 1, like this, for stride of 8:

    valgrind --tool=cachegrind ./sumvec -n 1048576 -s 8

Verify that for stride 1 and any other stride, the number of data references, D, are close to the same, but not identical (this is because the stride-1 function is still slightly different than the code for the stride function).

* What do you observe about the cache miss rate as the stride increases?

#### Cachegrind Output Files

Each time you run valgrind with the cachegrind tool, a new file gets written out in your workspace. You will see them if you do `ls` at the terminal. When you run `make clean`, all of the cachegrind output files will be removed.

These files contain more detail than we need to get into for this course (there is quite a bit of information you can find out about exactly which cache lines were used when). These files are mainly designed to be read by other programs. One of these is called `cg_annnotate`. If you want to try it you can send one of the output files as a command line argument to the program `cg_annotate` in the terminal.

## Two-Dimensional Array

Use valgrind with the cachegrind tool on the programs called `sumarrayrows` and `sumarraycols`.

* Is the difference in data miss rate what you would have expected?

## Three-Dimensional Array

The 3-D matrix program `sumarray3d.c` has been updated from memory activity 1 to take one optional command line argument, `-s`. If you run it with `-s` like this:

    ./sumarray3d -s

You will see that it runs the slower version of the code, which has poor spatial locality. You run the faster version with good spatial locality by not including the `-s` flag, like this:

    ./sumarray3d
    
Once you verify that the timing is slower for the version using the `-s` flag, use cachegrind to run each version.

* Do the reported number of cache misses indicate what you might expect, given the spatial locality of the data references?
