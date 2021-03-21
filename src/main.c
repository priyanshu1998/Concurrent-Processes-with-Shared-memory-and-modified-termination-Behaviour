/*
    Process Tree:

                         MAIN
                        /   \
           ...,P,P,P,P,P     C,C,C,C,C,...

There are cnt[0] producers
      and cnt[1] consumers
*/
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/mman.h>


int type_id = -1;
int parent_pid;


void Fork(int cnt){
    // int parent_pid = getpid();
    // while(cnt--){
    //     if(getpid()==parent_pid){
    //         fork();
    //     }
    //     else break;
    // }

    if(cnt){
        if(fork()>0){
            Fork(cnt-1);
        }
    }
}

void re_fork(int cnt){
    if(cnt){
        if(fork()==0){
            re_fork(cnt-1);
        }
    }
}

void type_Fork(int cnt, int type){
    Fork(cnt);                          //note only main parent process executes this line
    if(getpid() != parent_pid)
        type_id = type;
}

void gen_shared_mem(){
    int shm_fd = shm_open("prod_cons_shared_mem", O_CREAT|O_RDWR, 0666);
    ftruncate(shm_fd, 25*sizeof(int)); 
}

void rm_shared_mem(){
    shm_unlink("prod_cons_shared_mem"); 
}



int main(){
    parent_pid = getpid();
    gen_shared_mem();


    //int fd[2];
    //pipe(fd);

    int cnt[2],v; //cnt[0] : count of producers
                //cnt[1] : count of consumers
    sem_t *filled= sem_open("occupied",O_CREAT,0644,25); //Number of unfilled slots remaining  (does not have an item)
    sem_t *empty = sem_open("vaccant" ,O_CREAT,0644,0);  //Number of non-empty slots remaining (has an item)
    sem_t *mutex = sem_open("lock",O_CREAT,0644,1);      //binary semaphore
    sem_t *mutex_2=sem_open("outer_lock",O_CREAT,0644,1);//binary semaphore
    sem_t *tot = sem_open("TOTAL",O_CREAT,0644,0);       //tot count of produced value

    printf("Enter the number of producers : ");
    scanf("%d", cnt);
    sem_t *consumed = sem_open("tot_remains",O_CREAT,0644,cnt[0]);


    printf("Enter the number of consumers : ");
    scanf("%d",cnt+1);


    if(getpid() == parent_pid)type_Fork(cnt[0], 0); //producers
    if(getpid() == parent_pid)type_Fork(cnt[1], 1); //consumers


    switch (type_id)
    {
    case 0:
        //check producer.c for any logs
        //dup2(fd[1],2);
        //close(fd[0]);
        execl("./producers.out","producer","lock","occupied","vaccant","prod_cons_shared_mem",NULL);//exec producers
        exit(1);
        break;

    case 1:
        // check consumers.c for any log print
        //dup2(fd[0],0);
        //close(fd[1]);
        printf("consumer pid: %d\n",getpid());
        execl("./consumers.out","consumers","lock","outer_lock","occupied","vaccant","tot_remains","TOTAL","prod_cons_shared_mem",NULL);//exec consumers
        exit(1);
        break;
        
    default:
        break;
    }
    //close(fd[0]);
    //close(fd[1]);

    while(wait(0)>0);

    int val=0;
    sem_getvalue(tot,&val);
    printf("Value of TOTAL : %d\n",val);

    sem_unlink("occupied");
    sem_unlink("vaccant");
    sem_unlink("lock");
    sem_unlink("outer_lock");
    sem_unlink("TOTAL");
    sem_unlink("tot_remains");

    rm_shared_mem();
    return 0;
}