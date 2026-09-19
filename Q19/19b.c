/*
 * Shell equivalent to check state : ps -o pid,stat,cmd -p <pid>
 * Expected STAT column            : S
 */

#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Process ID: %d\n", getpid());
    printf("Process is sleeping...\n");

    while (1)
    {
        sleep(1);
    }

    return 0;
}
/*$ ./19b &
[1] 9042
Process ID: 9042
Process is sleeping...

$ ps -o pid,stat,cmd -p 9042
  PID STAT CMD
 9042 S    ./19b
$ kill 9042
*/
