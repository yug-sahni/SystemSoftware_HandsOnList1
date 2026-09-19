/*
 * Shell equivalent : none direct (fork() is a kernel-level operation)
 * Verify with       : cat output.txt
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    pid_t pid;

    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        close(fd);
        return 1;
    }

    if (pid == 0)
    {
        // Child process
        write(fd, "Child Process\n", 14);
    }
    else
    {
        // Parent process
        write(fd, "Parent Process\n", 15);
    }

    close(fd);

    return 0;
}
/*yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q21$ ./21
yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q21$ cat output.txt
Parent Process
Child Process
yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q21$ ./21
yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q21$ cat output.txt
Child Process
Parent Process
*/
