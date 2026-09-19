#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    pid_t pid;
    int hour, minute;
    time_t now;
    struct tm *current;

    printf("Enter hour (0-23): ");
    scanf("%d", &hour);

    printf("Enter minute (0-59): ");
    scanf("%d", &minute);

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid > 0)
    {
        printf("Daemon started. PID = %d\n", pid);
        exit(0);
    }

    // Create daemon
    setsid();

    // Step: change working directory to root
    chdir("/");

    // Step: reset file mode creation mask
    umask(0);

    // Step: close standard file descriptors (fully detach from terminal)
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1)
    {
        time(&now);
        current = localtime(&now);

        if (current->tm_hour == hour &&
            current->tm_min == minute)
        {
            FILE *fp;

            fp = fopen("/tmp/output.txt", "a");

            if (fp != NULL)
            {
                fprintf(fp, "Task executed at %02d:%02d\n",
                        current->tm_hour,
                        current->tm_min);

                fclose(fp);
            }

            break;
        }

        sleep(30);
    }

    return 0;
}
