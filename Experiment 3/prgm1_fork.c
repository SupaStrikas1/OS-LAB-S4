// Learn to create process - fork()

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main()
{
    pid_t p;
    p = fork();
    if (p < 0)
    {
        printf("Error. fork() failed.");
        exit(EXIT_FAILURE);
    }
    else if (p == 0)
    {
        printf("This is Child process, ID : %d\n", getpid());
    }
    else
    {
        printf("This is Parent process, ID : %d\n", getpid());
        wait(NULL);
    }
}