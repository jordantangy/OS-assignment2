#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h> 
#include <sys/wait.h>  

#define end_num 5
int flag = 1;
int fd[2];

void catch_sigusr1(int sig_num) {
   signal(SIGUSR1, catch_sigusr1);
}

void stop(int sig_num) {
   signal(SIGUSR2, stop);
   flag = 0;
}

void child_handler() {
    signal(SIGUSR1, catch_sigusr1);
    signal(SIGUSR2, stop);
    int x = 0;
    write(fd[1], &x, sizeof(int));
    pid_t ppid = getppid();
    kill(ppid, SIGUSR1);
    pause();
    while (flag){
        int x;
        read(fd[0], &x, sizeof(int));
        printf("%d\n",x);

        if (x >= end_num){
            sleep(1);
            kill(ppid, SIGUSR2);
            return;
        }
        x++;
        write(fd[1], &x, sizeof(int));
        sleep(1);
        kill(ppid, SIGUSR1);
        pause();
    }
}

void parent_handler(pid_t son_pid) {
    signal(SIGUSR1, catch_sigusr1);
    signal(SIGUSR2, stop);
    pause();
    while (flag){
        int x;
        read(fd[0], &x, sizeof(int));
        printf("%d\n",x);
        if (x >= end_num){
            sleep(1);
            kill(son_pid, SIGUSR2);
            return;
        }
        x++;
        write(fd[1], &x, sizeof(int));
        sleep(1);
        kill(son_pid, SIGUSR1);
        pause();
    }
}

int main() {
    signal(SIGUSR1, catch_sigusr1);
    signal(SIGUSR2, stop);
    pipe(fd);
    pid_t pid = fork();
    if (pid == -1){
        printf("Fork error\n");
        return -1;
    }
    if (pid == 0){
        child_handler();
    }
    else{
        parent_handler(pid);
    }

   if(pid == 0){
      printf("Child is going to be terminated\n");
      
   }
   else{
      printf("Parent is going to be terminated\n"); 
   }
   
   close(fd[1]);
   close(fd[0]);

   return 0;
}