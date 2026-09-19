#include <unistd.h>
#include <stdio.h>

int main(){
	if(link("original.txt", "hard.txt") == -1){
		perror("link");
		return 1;
	}
	else{
		printf("Hardlink created successfully\n");
	}
	return 0;
}
