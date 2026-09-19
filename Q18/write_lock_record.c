/*
 * Usage : ./write_lock_record <record_index>   (0, 1, or 2)
 * Expected output : Record 1 updated. New value: 1
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

struct record {
    int id;
    int value;
};

int main(int argc, char *argv[])
{
    int fd, index;
    struct record rec;
    struct flock lock;
    long offset;

    if (argc != 2)
    {
        printf("Usage: %s <record_index 0-2>\n", argv[0]);
        return 1;
    }

    index = atoi(argv[1]);
    offset = index * sizeof(struct record);

    fd = open("records.txt", O_RDWR);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = offset;
    lock.l_len = sizeof(struct record);

    printf("Waiting for write lock on record %d...\n", index);

    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("fcntl");
        close(fd);
        return 1;
    }

    lseek(fd, offset, SEEK_SET);
    read(fd, &rec, sizeof(rec));

    rec.value++;

    lseek(fd, offset, SEEK_SET);
    write(fd, &rec, sizeof(rec));

    printf("Record %d updated. New value: %d\n", index, rec.value);

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);

    return 0;
}
