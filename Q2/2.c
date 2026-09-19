#include <stdio.h>
#include<unistd.h>
int main(){
	for(;;){
		sleep(1);
	}
	return 0;
}
/*
 * PID=$!
echo $PID

ls /proc/$PID                     # everything the kernel exposes for this process
cat /proc/$PID/status             # name, state, PPid, memory usage, threads, etc.
cat /proc/$PID/cmdline            # exact command line that started it
cat /proc/$PID/stat               # raw stats: pid, state, ppid, utime, stime...
ls -l /proc/$PID/fd               # open file descriptors (0,1,2 = stdin/stdout/stderr)
cat /proc/$PID/maps               # memory-mapped regions
readlink /proc/$PID/cwd           # its current working directory
readlink /proc/$PID/exe           # path to the actual binary being run
cd /proc/[pid]/status | head */
