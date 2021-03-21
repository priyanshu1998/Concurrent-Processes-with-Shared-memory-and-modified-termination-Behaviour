
#include <stdio.h>
#include <semaphore.h>
#include <time.h> 
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>


int get_val(int arr[],int n){
    srand(getpid()+time(NULL));
    int i = rand()%n;
    int r_val = arr[i];
    arr[i] = arr[n-1];
    return r_val;
}



int main(int argc, char **argv){
    
    char buf[3];
    srand(getpid()+time(NULL));
    int consumer_val = rand()%80+1;;

    sem_t  *mutex,*mutex_2, *filled, *empty, *consumed, *tot;
    
    if(argc != 8) {
        printf("INVALID NUMBER OF ARGUMENTS DETECTED.\nPROGRAM IS EXITING.\n");
        return 0;
    }

    int shm_fd = shm_open(argv[7], O_RDWR, 0666); int n, val;
    int* arr = (int*)mmap(0, 25*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0); 


    //if(argc == 8){
        mutex  = sem_open(argv[1],0); //lock(mutex)
        mutex_2 = sem_open(argv[2],0);
        filled = sem_open(argv[3],0); //buffer space filled 
        empty  = sem_open(argv[4],0); //buffer space empty
        consumed = sem_open(argv[5],0);
        tot = sem_open(argv[6],0);
                


        
        
        sem_wait(mutex_2);                     
            int v;
            sem_getvalue(consumed,&v);
            if(v==0){
                printf("Exiting consumer Process\n");
                shm_unlink(argv[7]); 
                sem_post(mutex_2);
                exit(0);
            }

        sem_wait(empty);                        //check if item exist in buffer                     
            sem_wait(mutex);                    //lock(mutex)
    //}

    //*******************************************************************
                /*Critical Section*/
                // read(0, buf, 2);
                // close(0);
                // buf[3] = '\0';
                // sscanf(buf,"%d",&consumer_val);
                sem_getvalue(empty,&n);
                val = get_val(arr,n+1); // +1 for decrement caused by sem_wait
                for(int i=0;i<val;i++) sem_post(tot);

                printf("added %d\n",val);
                

    //*******************************************************************


    //if(argc == 8){
                sem_wait(consumed);            //item is consumed by which was produced by some producer
                sem_post(filled);              //item is taken hence filled is incremented
            sem_post(mutex);                   //unlock
        sem_post(mutex_2);

        
        sem_close(tot);
        sem_close(empty);
        sem_close(filled);
        sem_close(mutex);
        sem_close(mutex_2);
        sem_close(consumed);




        execl("./consumers.out","consumers","lock","outer_lock","occupied","vaccant","tot_remains","TOTAL","prod_cons_shared_mem",NULL);
        //exec the process again.
    //} 
      
    return 0;
}