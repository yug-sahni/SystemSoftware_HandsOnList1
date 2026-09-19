/*
 * Shell equivalent : none direct (fork() is a kernel-level operation)
 */

#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        // Child process
        printf("Child Process ID  : %d\n", getpid());
        printf("Parent Process ID : %d\n", getppid());
    }
    else
    {
        // Parent process
        printf("Parent Process ID : %d\n", getpid());
        printf("Child Process ID  : %d\n", pid);
    }

    return 0;
}
/*
 parent and child process can print differently no sync run a few times and it will be visible*/
