/*
 * Shell equivalent : stat filename
 * Usage            : ./fileinfo file.txt
 */

#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

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

    printf("Inode number       : %ld\n", s.st_ino);
    printf("Hard links         : %ld\n", s.st_nlink);
    printf("UID                : %d\n", s.st_uid);
    printf("GID                : %d\n", s.st_gid);
    printf("Size               : %ld bytes\n", s.st_size);
    printf("Block size         : %ld bytes\n", s.st_blksize);
    printf("Number of blocks   : %ld\n", s.st_blocks);

    printf("Last access        : %s", ctime(&s.st_atime));
    printf("Last modification  : %s", ctime(&s.st_mtime));
    printf("Last change        : %s", ctime(&s.st_ctime));

    return 0;
}
