/*
 * Shell equivalent : none direct (dup() is a kernel-level fd operation)
 * Expected output  : File updated successfully.
 * Verify with       : cat file.txt
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd, fd2;

    fd = open("fileA.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    fd2 = dup(fd);

    if (fd2 == -1)
    {
        perror("dup");
        close(fd);
        return 1;
    }

    write(fd, "Using fd\n", 9);
    write(fd2, "Using duplicated fd\n", 20);

    close(fd);
    close(fd2);

    printf("File updated successfully.\n");

    return 0;
}
