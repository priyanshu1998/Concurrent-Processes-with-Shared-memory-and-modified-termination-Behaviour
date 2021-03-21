# Concurrent-Processes-with-Shared-memory-and-modified-termination-Behaviour
 Architecture for synchronizing concurrent processes that have a shared memory space and modified termination behaviour.

Language: C 



## Motivation:

The architecture was created to solve a concurrency, termination behavior problem of a 3rd Year Assignment in OS.
The problem is a modification of the producer-consumer problem.

    Objectives:
    - Create a shared space for the processes.
    - Synchronize producer and consumer processes.
    - consumer processes don't terminate unless all producer processes have terminated.
        (each producer process creates a value and terminates.)

## Problem Statement:

    Write a program for p-producer c-consumer problem, p, c >= 1.
    A shared circular buffer that can hold 25 items is to be used. 
    Each producer process stores any numbers between 1 to 80 (along with the producer id) in the buffer one by one and then exits. 
    Each consumer process reads the numbers from the buffer and adds them to a shared variable TOTAL (initialized to 0). 
         
    Though any consumer process can read any of the numbers in the buffer, 
    the only constraint being that every number written by some producer should be read exactly once by exactly one of the consumers. 
    The program reads in the value of p and c from the user and forks p producers and c consumers.
      
    After all the producers and consumers have finished 
    (the consumers' exit after all the data produced by all producers have been read), 
    the parent process prints the value of TOTAL.  
        
        
    Test the program with different values of p and c.


## Challenge:

Note the termination behavior is not a standard.
One needs to code a consumer process but its termination depends on a set of other processes.

 Solving this challenge makes one of the best assignment I have ever coded.


#### Compile:

    g++ main.c -lpthread -lrt -o main.out
    g++ consumers.c -lpthread -lrt -o consumers.out
    g++ producers.c -lpthread -lrt -o producers.out 

### Execute:
    ./main.out


## References:
UNIX System Programming Using C++ 
https://www.amazon.in/UNIX-System-Programming-Using-C/dp/9332549974

