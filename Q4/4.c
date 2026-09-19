#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	int fd;

	fd = open("excltest.txt", O_CREAT | O_EXCL | O_WRONLY, 0644);
	if(fd == -1){
		perror("open");
		return 1;
	}

	printf("File created successfully. fd = %d\n", fd);

	close(fd);
	return 0;
}
/*O_CREAT | O_EXCL together are special: normally O_CREAT alone creates the file if missing and just opens it if it already exists. Adding O_EXCL changes that — if the file already exists, open() fails immediately with EEXIST instead of opening it.*/
