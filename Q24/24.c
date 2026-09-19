/*
 * Shell equivalent : none direct (fork/waitpid are kernel-level operations)
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t child[3];
    int i;

    // Create 3 child processes
    for (i = 0; i < 3; i++)
    {
        child[i] = fork();

        if (child[i] < 0)
        {
            perror("fork failed");
            return 1;
        }

        if (child[i] == 0)
        {
            printf("Child %d: PID = %d\n", i + 1, getpid());

            sleep((i + 1) * 2);

            printf("Child %d exiting...\n", i + 1);
            exit(0);
        }
    }

    // Parent waits specifically for Child 2
    printf("Parent waiting for Child 2...\n");

    waitpid(child[1], NULL, 0);

    printf("Child 2 has finished.\n");

    // Wait for remaining children
    waitpid(child[0], NULL, 0);
    waitpid(child[2], NULL, 0);

    printf("Parent exiting.\n");

    return 0;
}
/*yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q24$ ./24
Child 1: PID = 21869
Parent waiting for Child 2...
Child 3: PID = 21871
Child 2: PID = 21870
Child 1 exiting...
Child 2 exiting...
Child 2 has finished.
Child 3 exiting...
Parent exiting.
yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q24$ ./24
Child 1: PID = 21878
Child 2: PID = 21879
Parent waiting for Child 2...
Child 3: PID = 21880
Child 1 exiting...
Child 2 exiting...
Child 2 has finished.
Child 3 exiting...
Parent exiting.
*/
