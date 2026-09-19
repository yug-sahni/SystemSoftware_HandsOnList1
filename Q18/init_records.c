/*
 * Run once to create the records file.
 * Expected output : Records initialized.
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

struct record {
    int id;
    int value;
};

int main()
{
    int fd;
    struct record recs[3];
    int i;

    for (i = 0; i < 3; i++)
    {
        recs[i].id = i;
        recs[i].value = 0;
    }

    fd = open("records.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    write(fd, recs, sizeof(recs));

    close(fd);

    printf("Records initialized.\n");

    return 0;
}
/*$ ./init_records
Records initialized.

$ ./write_lock_record 1
Waiting for write lock on record 1...
Record 1 updated. New value: 1

$ ./write_lock_record 1
Waiting for write lock on record 1...
Record 1 updated. New value: 2

$ ./read_lock_record 0
Waiting for read lock on record 0...
Record 0: id=0, value=0

$ ./read_lock_record 1
Waiting for read lock on record 1...
Record 1: id=1, value=2
*/
