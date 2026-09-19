#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Caller PID = %d, about to exec ./25b_i\n", getpid());

    execl("./25b_i", "25b_i", "yug", NULL);

    perror("execl failed");
    return 1;
}
