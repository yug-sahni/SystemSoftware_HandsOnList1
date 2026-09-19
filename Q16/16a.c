/*
 * Shell equivalent : flock -x file.txt sleep 30   (advisory lock via shell)
 * Expected output  : Trying to acquire write lock...
 *                     Write lock acquired.
 *                     Press Enter to release the lock...
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    struct flock lock;

    fd = open("file.txt", O_RDWR);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    printf("Trying to acquire write lock...\n");

    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Write lock acquired.\n");
    printf("Press Enter to release the lock...\n");
    getchar();

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    printf("Write lock released.\n");

    close(fd);

    return 0;
}
/*
 gcc 16a.c -o 16a
echo "test data" > file.txt

# Terminal 1:
./16a
# prints "Write lock acquired." and waits at getchar()

# Terminal 2 (while Terminal 1 is still waiting):
./16a
# this one will print "Trying to acquire write lock..." and then BLOCK,
# because F_SETLKW waits for Terminal 1 to release it first
*/
