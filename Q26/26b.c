#include <stdio.h>
#include <unistd.h>

int main()
{
    execlp("ls", "ls", "-R", "-l", NULL);

    perror("execlp failed");

    return 1;
}
