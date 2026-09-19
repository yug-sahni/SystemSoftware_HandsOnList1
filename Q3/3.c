/*
 * Shell equivalent : touch newfile.txt   (roughly — creat() also truncates
 *                     an existing file to 0 bytes, touch does not)
 * Expected output  : File descriptor value : 3
 */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	int fd;

	fd = creat("newfile.txt", 0644);
	if(fd == -1){
		perror("creat");
		return 1;
	}

	printf("File created successfully\n");
	printf("File descriptor value : %d\n", fd);

	close(fd);
	return 0;
}
