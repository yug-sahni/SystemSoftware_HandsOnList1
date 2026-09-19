#include <stdio.h>
#include <unistd.h>

int main()
{
    char *args[] = {"ls", "-R", "-l", NULL};

    execv("/bin/ls", args);

    perror("execv failed");

    return 1;
}
