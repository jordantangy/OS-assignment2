#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#define end_num 5
int fd[2];
int returnval;


void stop(int sig) {
    printf("Parent is going to be terminated");
    exit(0);
}

void stopC(){
    printf("Child is going to be terminated");
    int parent_id = getppid();
    kill(parent_id, stop);
    exit(0);
}

void parent_handler(){
    signal(SIGUSR1, child_handler);
    int x;
    read(fd[1],&x,sizeof(int));
    printf("%d/n",x);
    if (x == end_num){
        stopC();
    }
    x++;
    write(fd[0],&x,sizeof(int));
    close(fd[0]);
    kill(,SIGUSR1)
}
void child_handler(){
    signal(SIGUSR1, parent_handler);
    int x;
    read(fd[0],&x,sizeof(int));
    printf("%d/n",x);
    if (x == end_num){
        stopC();
    }
    x++;
    write(fd[1],&x,sizeof(int));
    close(fd[1]);
    int parent_id = getppid();
    kill(parent_id, SIGUSR1);
}

int main(){
    returnval = pipe(fd);
    if(returnval == -1 ){
        printf("An error occured while opening the pipe\n");
        return 1;
    }

    pid_t pid = fork();
    int parent_id = getppid();
    if(pid == 0){
        int x = 0;
        write(fd[1],&x,sizeof(int));
        close(fd[1]);
        signal(SIGUSR1, parent_handler);
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

