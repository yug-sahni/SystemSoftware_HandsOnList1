#include <unistd.h>
#include <stdio.h>

int main(){
	if(symlink("original.txt", "soft.txt") == -1){
		perror("symlink");
		return 1;
	}
	else{
		printf("Softlink created successfully\n");
	}
	return 0;
}
