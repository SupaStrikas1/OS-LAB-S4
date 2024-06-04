// Running sub-process – fork(), exec()

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
        printf("Child process (PID: %d) executing ...\n", getpid());
        char *args[] = {"./abc", NULL};
        execvp(args[0], args);
    }
    else
    {
        wait(NULL);
        printf("\nChild process completed.\n");
    }
}