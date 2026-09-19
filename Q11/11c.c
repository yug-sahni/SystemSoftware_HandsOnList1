/*
 * Shell equivalent : none direct (fcntl() is a kernel-level fd operation)
 * Expected output  : File updated successfully.
 * Verify with       : cat file.txt
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd, fd2;

    fd = open("file.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    fd2 = fcntl(fd, F_DUPFD, 10);

    if (fd2 == -1)
    {
        perror("fcntl");
        close(fd);
        return 1;
    }

    write(fd, "Using fd\n", 9);
    write(fd2, "Using fcntl\n", 12);

    close(fd);
    close(fd2);

    printf("File updated successfully.\n");

    return 0;
}
