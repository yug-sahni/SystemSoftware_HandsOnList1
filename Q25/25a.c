#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Before exec: PID = %d\n", getpid());

    execlp("ls", "ls", "-l", NULL);

    // this line only runs if execlp() FAILS
    perror("execlp failed");
    return 1;
}
