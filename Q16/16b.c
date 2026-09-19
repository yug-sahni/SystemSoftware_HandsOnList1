/*
 * Shell equivalent : flock -s file.txt sleep 30   (shared/advisory lock via shell)
 * Expected output  : Trying to acquire read lock...
 *                     Read lock acquired.
 *                     Press Enter to release the lock...
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    struct flock lock;

    fd = open("file.txt", O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    printf("Trying to acquire read lock...\n");

    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Read lock acquired.\n");
    printf("Press Enter to release the lock...\n");
    getchar();

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    printf("Read lock released.\n");

    close(fd);

    return 0;
}
/*# Terminal 1:
./readlock
# "Read lock acquired." then waits

# Terminal 2 (while Terminal 1 is still holding its lock):
./readlock
# should ALSO immediately print "Read lock acquired." — no blocking!
*/
