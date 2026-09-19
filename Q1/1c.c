#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(){
	if(mknod("myfifo", S_IFIFO | 0666, 0) == -1){
		perror("mknod");
		return 1;
	}
	else{
		printf("FIFO created successfully\n");
	}
	return 0;
}
