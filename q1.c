#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>


void parent_handler(int num){
 

}
void child_handler(int num){

  

}

int main(){
    

    int fd[2];
    int returnval;
    returnval = pipe(fd);
    if(returnval == -1 ){
        printf("An error occured while opening the pipe\n");
        return 1;
    }

    pid_t pid = fork();
    int parend_id = getppid();
    if(pid == 0){
        int x = 0;
        write(fd[1],&x,sizeof(int));
        signal(SIGUSR1,parend_id);
        close(fd[1]);

    }
   
   

}

