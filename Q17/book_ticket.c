/*
 * Run this each time someone "books" a ticket.
 * Expected output (1st run) : New ticket number: 101
 * Expected output (2nd run) : New ticket number: 102
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    int ticket;
    struct flock lock;

    fd = open("ticket.txt", O_RDWR);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // Create write lock
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    printf("Waiting for write lock...\n");

    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Write lock acquired.\n");

    // Read current ticket number
    read(fd, &ticket, sizeof(ticket));

    // Increment ticket number
    ticket++;

    // Go back to beginning of file
    lseek(fd, 0, SEEK_SET);

    // Store new ticket number
    write(fd, &ticket, sizeof(ticket));

    printf("New ticket number: %d\n", ticket);

    // Release lock
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);

    return 0;
}
