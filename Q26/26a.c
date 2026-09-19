#include <stdio.h>
#include <unistd.h>

int main()
{
    execl("/bin/ls", "ls", "-R", "-l", NULL);

    perror("execl failed");

    return 1;
}
