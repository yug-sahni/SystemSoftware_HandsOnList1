/*
 * Shell equivalent to check reparenting : ps -o pid,ppid,cmd -p <child_pid>
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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
        printf("Child started.\n");
        printf("Child PID  : %d\n", getpid());
        printf("Parent PID : %d\n", getppid());

        sleep(10);

        printf("\nAfter parent exits:\n");
        printf("Child PID  : %d\n", getpid());
        printf("Parent PID : %d\n", getppid());
    }
    else
    {
        // Parent process
        printf("Parent PID : %d\n", getpid());
        printf("Parent exiting...\n");

        exit(0);
    }

    return 0;
}
/*yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q23$ ps -o pid,ppid,cmd -p 21758
    PID    PPID CMD
  21758    3100 ./23
yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q23$ ps -o pid,ppid,cmd -p 21758
    PID    PPID CMD
*/
