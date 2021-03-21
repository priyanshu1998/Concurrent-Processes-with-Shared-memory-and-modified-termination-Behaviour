#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h> 
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>



int main(int argc, char **argv){
    printf("Producer pid: %d \n",getpid());

    if(argc != 5) {
        printf("INVALID NUMBER OF ARGUMENTS DETECTED.\nPROGRAM IS EXITING.\n");
        return 0;
    }
    
    sem_t *mutex, *filled, *empty;
    int shm_fd = shm_open(argv[4],O_RDWR, 0666); int n;
    int* arr = (int*)mmap(0, 25*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    srand(getpid()+time(NULL));
    int produced_val = rand()%80+1;
    char buf[3];
    if(produced_val>9){
        sprintf(buf,"%d",produced_val);  
    }else{
        buf[0]='0';
        buf[1]=(int)'0'+ produced_val;
        buf[2]='\0';
    }
    
    //if(argc == 5){
        mutex  = sem_open(argv[1],0); //lock(mutex)
        filled = sem_open(argv[2],0); //Number of unfilled slots remaining
        empty  = sem_open(argv[3],0); //Number of non-empty slots remaining

        
        sem_wait(filled);                 //Check if unfilled slot exist
            sem_wait(mutex);//}             //lock if possible
    //******************************************************
                //write(2,buf,2);           //Critical Section
                //close(2);
                //printf("Produced %d\n",produced_val);
                 sem_getvalue(empty,&n);
                arr[n]=produced_val;
                printf("ProducedVal\n");
    //******************************************************            
    // if(argc == 5){
            sem_post(empty);          //empty slot is taken hence decrement
        sem_post(mutex);              //unlock     
        sem_close(empty);
        sem_close(filled);           
        sem_close(mutex);
        
    // }
    return 0;
}