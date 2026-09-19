#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	int fd;
	char filename[30];
	int i, round = 0;

	while(1){
		for(i = 1; i <= 5; i++){
			sprintf(filename, "file_%d_%d.txt", round, i);

			fd = open(filename, O_CREAT | O_WRONLY, 0644);
			if(fd == -1){
				perror("open");
				continue;
			}

			printf("Created %s with fd = %d\n", filename, fd);
			/* NOT closing fd on purpose, so the descriptor table keeps
			 * growing and is visible in /proc/<pid>/fd                */
		}
		round++;
		sleep(5);
	}

	return 0;
}
/*yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q5$ vim 5.c
yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q5$ gcc 5.c -o 5
yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q5$ ./5 > log.txt &
[1] 8495
yugsahni@Ubuntu:~/Desktop/HandsOnList-1/Q5$ ls -l /proc/8495/fd 

 * */
