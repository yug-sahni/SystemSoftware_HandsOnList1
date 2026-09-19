/*
 * Shell equivalent to check zombie state : ps -l   (STAT column shows Z)
 *                                          or: ps aux | grep defunct
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
        printf("Child process: PID = %d\n", getpid());
        printf("Child exiting...\n");
        exit(0);
    }
    else
    {
        // Parent process
        printf("Parent process: PID = %d\n", getpid());
        printf("Child PID = %d\n", pid);

        printf("Parent sleeping...\n");
        sleep(30);

        printf("Parent exiting...\n");
    }

    return 0;
}
/*
 yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q22$ ./22 &
[1] 21582
Parent process: PID = 21582
Child PID = 21584
Parent sleeping...
Child process: PID = 21584
Child exiting...
yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q22$ ps -l
F S   UID     PID    PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
0 S  1000   21299   21264  0  80   0 -  2856 do_wai pts/0    00:00:00 bash
0 S  1000   21582   21299  0  80   0 -   692 hrtime pts/0    00:00:00 22
1 Z  1000   21584   21582  0  80   0 -     0 -      pts/0    00:00:00 22
0 R  1000   21585   21299  0  80   0 -  3134 -      pts/0    00:00:00 ps

*/
