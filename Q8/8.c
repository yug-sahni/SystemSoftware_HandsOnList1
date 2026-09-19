/*
 * Shell equivalent : cat file.txt
 * Expected output  : file.txt printed line by line
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char ch;
    char line[200];
    int i;

    fd = open("file.txt", O_RDONLY);

    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    i = 0;
    while (read(fd, &ch, 1) > 0)
    {
        if (ch == '\n')
        {
            line[i] = '\n';
            write(1, line, i + 1);     /* display the completed line */
            i = 0;                     /* reset buffer for next line */
        }
        else
        {
            line[i] = ch;
            i++;
        }
    }

    if (i > 0)                          /* last line with no trailing \n */
    {
        write(1, line, i);
    }

    close(fd);

    return 0;
}
