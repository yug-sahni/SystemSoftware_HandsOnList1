/*
 * Shell equivalent : ls -l   (first character of permission string:
 *                     - regular, d directory, l symlink, p FIFO,
 *                     c char device, b block device, s socket)
 * Usage            : ./filetype <filename>
 */

#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    struct stat s;

    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    if (stat(argv[1], &s) == -1)
    {
        perror("Error");
        return 1;
    }

    if (S_ISREG(s.st_mode))
        printf("Regular file\n");

    else if (S_ISDIR(s.st_mode))
        printf("Directory\n");

    else if (S_ISLNK(s.st_mode))
        printf("Symbolic link\n");

    else if (S_ISFIFO(s.st_mode))
        printf("FIFO (Named Pipe)\n");

    else if (S_ISCHR(s.st_mode))
        printf("Character device\n");

    else if (S_ISBLK(s.st_mode))
        printf("Block device\n");

    else if (S_ISSOCK(s.st_mode))
        printf("Socket\n");

    else
        printf("Unknown file type\n");

    return 0;
}
/*yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q14$ ./14 p
FIFO (Named Pipe)
yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q14$ ./14 /dev/sda
Block device
yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q14$ ./14 file.txt
Regular file
*/
