#include <stdio.h>
#include <unistd.h>
#include <sched.h>

int main()
{
    int policy;
    struct sched_param param;

    // Get current scheduling policy
    policy = sched_getscheduler(0);

    if (policy == -1)
    {
        perror("sched_getscheduler");
        return 1;
    }

    if (policy == SCHED_OTHER)
        printf("Current policy: SCHED_OTHER\n");
    else if (policy == SCHED_FIFO)
        printf("Current policy: SCHED_FIFO\n");
    else if (policy == SCHED_RR)
        printf("Current policy: SCHED_RR\n");

    // Set priority
    param.sched_priority = 10;

    // Change policy to SCHED_FIFO
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1)
    {
        perror("sched_setscheduler");
        return 1;
    }

    printf("Scheduling policy changed to SCHED_FIFO\n");

    // Get policy again
    policy = sched_getscheduler(0);

    if (policy == SCHED_FIFO)
        printf("Current policy: SCHED_FIFO\n");

    return 0;
}
/*without sudo not permitted
 $ sudo ./29
Current policy: SCHED_OTHER
Scheduling policy changed to SCHED_FIFO
Current policy: SCHED_FIFO*/
