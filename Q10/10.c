/*
 * Shell equivalent : none direct — inspect the result with:  od -c file.txt
 * Expected output  : File pointer is now at position: 20
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char data1[] = "ABCDEFGHIJ";
    char data2[] = "1234567890";
    int pos;

    fd = open("file.txt", O_RDWR | O_CREAT, 0644);

    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    // Write first 10 bytes
    write(fd, data1, 10);

    // Move file pointer 10 bytes forward
    pos = lseek(fd, 10, SEEK_CUR);

    if (pos == -1)
    {
        perror("lseek failed");
        close(fd);
        return 1;
    }

    printf("File pointer is now at position: %d\n", pos);

    // Write another 10 bytes
    write(fd, data2, 10);

    close(fd);

    return 0;
}
/*yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q10$ wc -c file.txt
30 file.txt
---------------here file size is 30 not 20 this means offset works--------------
yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q10$ ls -l file.txt
-rw-r--r-- 1 yugsahni yugsahni 30 Sep 19 11:13 file.txt
*/
