/*
 * Shell equivalent : none direct (fcntl F_GETFL has no shell equivalent)
 * Expected output  : File is opened in READ-WRITE mode.
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd, flags, mode;

    fd = open("file.txt", O_RDWR);

    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    flags = fcntl(fd, F_GETFL);

    if (flags == -1)
    {
        perror("fcntl error");
        close(fd);
        return 1;
    }

    mode = flags & O_ACCMODE;

    if (mode == O_RDONLY)
        printf("File is opened in READ ONLY mode.\n");
    else if (mode == O_WRONLY)
        printf("File is opened in WRITE ONLY mode.\n");
    else if (mode == O_RDWR)
        printf("File is opened in READ-WRITE mode.\n");

    close(fd);

    return 0;
}
/*yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q12$ echo "test" > file.txt
yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q12$ ./12
File is opened in READ-WRITE mode.
*/
