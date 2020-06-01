#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>

int fd[2];
int returnval;

void parent_handler(){
    
    


}
void child_handler(){
    int x = 0;
    write(fd[1],&x,sizeof(int));
    signal(SIGUSR1,parent_handler);
    close(fd[1]);
}

int main(){
    returnval = pipe(fd);
    if(returnval == -1 ){
        printf("An error occured while opening the pipe\n");
        return 1;
    }

    pid_t pid = fork();
    int parend_id = getppid();
    if(pid == 0){
        child_handler();
    }
    else{
        parent_handler();
    }
}

