#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "q1.h"

#define end_num 5
int fd[2];
int returnval;


void parent_handler(int signum){
    int x;
    read(fd[0],&x,sizeof(int));
    printf("%d/n",x);
    if (x == end_num){
        //TODO
    }
    x++;
    write(fd[1],&x,sizeof(int));
    close(fd[1]);
    //signal(SIGUSR1, child_handler);
}

void child_handler(int signum){
    int x;
    read(fd[0],&x,sizeof(int));
    printf("%d/n",x);
    if (x == end_num){
        //TODO
    }
    x++;
    write(fd[1],&x,sizeof(int));
    close(fd[1]);
    int parent_id = getppid();
    signal(SIGUSR1, parent_handler);
    kill(parent_id, SIGUSR1);
}

int main(){
    returnval = pipe(fd);
    if(returnval == -1 ){
        printf("An error occured while opening the pipe\n");
        return 1;
    }
    signal(SIGUSR1, parent_handler);
    pid_t pid = fork();
    int parent_id = getppid();
    if(pid == 0){
        int x = 0;
        write(fd[1],&x,sizeof(int));
        close(fd[1]);
        kill(parent_id, SIGUSR1);
        while(1){
            sleep(1);
        }
    }
    else{
        while(1){
            sleep(1);
        }
    }
}

