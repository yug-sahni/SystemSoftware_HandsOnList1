#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

int main()
{
    int priority;

    priority = getpriority(PRIO_PROCESS, 0);

    printf("Current priority: %d\n", priority);
    printf("Process ID: %d\n", getpid());
    printf("Run the following command to change priority:\n");
    printf("sudo renice -n 5 -p %d\n", getpid());

    printf("Sleeping for 30 seconds so you can renice this process...\n");
    sleep(30);

    priority = getpriority(PRIO_PROCESS, 0);
    printf("Priority after renice attempt: %d\n", priority);

    return 0;
}
/*
 $ ./28
Current priority: 0
Process ID: 23110
Run the following command to change priority:
sudo renice -n 5 -p 23110
Sleeping for 30 seconds so you can renice this process...
Priority after renice attempt: 5
*/
