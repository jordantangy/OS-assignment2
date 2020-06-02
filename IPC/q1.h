#pragma once
#include <sys/types.h>

void catch_sigusr1(int sig_num);
void stop(int sig_num);
void child_handler();
void parent_handler(pid_t son_pid);