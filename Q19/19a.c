/*
 * Shell equivalent to check state : ps -o pid,stat,cmd -p <pid>
 * Expected STAT column            : R  (or R+ if run in foreground)
 */

#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Process ID: %d\n", getpid());
    printf("Process is running (busy loop, no sleep)...\n");

    unsigned long i = 0;

    while (1)
    {
        i++;   /* pure CPU work, never blocks */
    }

    return 0;
}
/*
 $ ./19a &
[1] 8213
Process ID: 8213
Process is running (busy loop, no sleep)...

$ ps -o pid,stat,cmd -p 8213
  PID STAT CMD
 8213 R+   ./running

$ kill 8213*/
