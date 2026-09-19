/*
 * Shell equivalent : cp file1 file2
 * Usage            : ./filecopy source.txt dest.txt
 * Expected output  : File copied successfully.
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd1, fd2;
    char buffer[100];
    int n;

    if (argc != 3)
    {
        printf("Usage: %s file1 file2\n", argv[0]);
        return 1;
    }

    fd1 = open(argv[1], O_RDONLY);

    if (fd1 == -1)
    {
        perror("Error opening source file");
        return 1;
    }

    fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd2 == -1)
    {
        perror("Error opening destination file");
        close(fd1);
        return 1;
    }

    while ((n = read(fd1, buffer, sizeof(buffer))) > 0)
    {
        write(fd2, buffer, n);
    }

    close(fd1);
    close(fd2);

    printf("File copied successfully.\n");

    return 0;
}
