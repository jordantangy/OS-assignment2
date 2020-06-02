#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h> 
#include <sys/wait.h>  

#define end_num 5

int val = 0;
int fd[2];

int raiseNumber()
{
   int x = 0;
   read(fd[0], &x, sizeof(x));
   //printf("val is = %d\n", x);
   printf("%d\n", x);
   val = x + 1;
   write(fd[1], &val, sizeof(val));
   return val;
}

void catch_sigusr1(int sig_num)
{
   signal(SIGUSR1, catch_sigusr1);
   //printf("im a signal sigusr1", getpid());
}

void child_handler()
{
 
   sleep(1);
   if (val < end_num)
      raiseNumber();
   kill(getppid(), SIGUSR1);
   pause();
}

void parent_handler(pid_t son_pid)
{
   //printf("hey\n");
   //printf("pid of dad = %d, pid of son = %d\n", getpid(), son_pid);

   pause();
   if (val < end_num)
      raiseNumber();
   kill(son_pid, SIGUSR1);
}

int main()
{
   pipe(fd);
   write(fd[1], &val, sizeof(val));
   pid_t pid;
   pid = fork();
   signal(SIGUSR1, catch_sigusr1);
   while (val < end_num)
   {
      sleep(1);
      switch (pid)
      {
      case -1:
         printf("Fork error\n");
         return -1;
         break;
      case 0:
      printf("son\n");
         child_handler();
         break;

      default:
       printf("dad\n");
         parent_handler(pid);
         
      }
   }
   if(pid == 0){
      printf("Child is going to be terminated\n");
      kill(pid, SIGKILL);
      
   }
   else{
      printf("Parent is going to be terminated\n");
      kill(pid, SIGKILL);
      
   }
   
   close(fd[1]);
   close(fd[0]);

   return 0;
}