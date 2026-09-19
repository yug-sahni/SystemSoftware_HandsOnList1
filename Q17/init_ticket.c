/*
 * Run once to initialize the ticket file.
 * Expected output : Initial ticket number: 100
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    int ticket = 100;

    fd = open("ticket.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    write(fd, &ticket, sizeof(ticket));

    close(fd);

    printf("Initial ticket number: %d\n", ticket);

    return 0;
}
