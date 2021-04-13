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
(also the "set of processes" are not child processes of consumers and hence api such as wait(...) wont work and also for different values of p and c one needs to ensure there is no deadlock)

#### Compile:

    g++ ./src/main.c -lpthread -lrt -o ./bin/main.out
    g++ ./src/consumers.c -lpthread -lrt -o ./bin/consumers.out
    g++ ./src/producers.c -lpthread -lrt -o ./bin/producers.out 

### Execute:
    # It is important to cd into bin as exec assumes "consumers.out" and "producers.out" are in same folder as "main.out"
    # Not changing directory can result in undefined behaviour. 
    cd ./bin
    ./main.out


## References:
UNIX System Programming Using C++ - Terrence Chan
https://www.amazon.in/UNIX-System-Programming-Using-C/dp/9332549974


## Test Run:
![image](https://user-images.githubusercontent.com/36814207/114513356-ba807280-9c57-11eb-96d3-fa7f3558e486.png)


