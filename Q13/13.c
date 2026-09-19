/*
 * Shell equivalent : read -t 10 line   (bash's own timed-read builtin)
 * Expected output (if you type within 10s) : Data is available on STDIN.
 *                                             Input received: <your text>
 * Expected output (if you type nothing)     : No input received within 10 seconds.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

int main()
{
    fd_set readfds;
    struct timeval timeout;
    char buffer[100];

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for input for 10 seconds...\n");

    int result = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

    if (result == -1)
    {
        perror("select");
    }
    else if (result == 0)
    {
        printf("No input received within 10 seconds.\n");
    }
    else
    {
        if (FD_ISSET(STDIN_FILENO, &readfds))
        {
            printf("Data is available on STDIN.\n");

            int n = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

            if (n > 0)
            {
                buffer[n] = '\0';
                printf("Input received: %s", buffer);
            }
        }
    }

    return 0;
}
/*./13
Waiting for input for 10 seconds...
this is the new text input [Enter]        ← press Enter within 10 seconds
Data is available on STDIN.
Input received: sddfdfwef*/
