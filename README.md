# EGC 301P — Operating Systems Lab

Solutions to lab exercises **1–30** of the EGC 301P Operating Systems Lab, covering **File Management** (Q1–Q18) and **Process Management** (Q19–Q30). All programs are written in C against the Linux/POSIX system call interface.

---

## Contents

- [Build and Run](#build-and-run)
- [Part I — File Management (Q1–Q18)](#part-i--file-management-q1q18)
- [Part II — Process Management (Q19–Q30)](#part-ii--process-management-q19q30)
- [Quick Reference Table](#quick-reference-table)

---

## Build and Run

**Requirements:** Linux, `gcc`, `make` (optional). A few programs (Q16, Q27–Q29) need `sudo` for certain operations.

```bash
# compile a single exercise
gcc q1.c -o q1

# run
./q1

# compile everything
for f in q*.c; do gcc "$f" -o "${f%.c}"; done
```

> File names follow the pattern `qN.c` (e.g. `q7.c`). Exercises with sub-parts use `qNa.c`, `qNb.c`, … and exercises that need two cooperating programs use `qN_1.c` / `qN_2.c`.

---

## Part I — File Management (Q1–Q18)

### Q1. Creating Different File Types
Create special files using both shell commands and system calls:
- **a.** Soft link — `symlink()`
- **b.** Hard link — `link()`
- **c.** FIFO — `mkfifo()` library function or `mknod()` system call

```bash
# shell equivalents
ln -s target softlink
ln target hardlink
mkfifo myfifo        # or: mknod myfifo p
ls -l                # verify: 'l' for symlink, 'p' for FIFO, link count for hard link
```

### Q2. Background Process Exploration
A program that runs forever (`while(1);`). Run it in the background and inspect its entry in `/proc`.

```bash
./q2 &
cat /proc/<pid>/status
ls -l /proc/<pid>/
```

### Q3. File Creation and Descriptor Printing
Create a file with `creat()` and print the returned file descriptor (typically `3`, since 0/1/2 are taken by stdin/stdout/stderr).

### Q4. Opening an Existing File
Open an existing file in read-write mode (`O_RDWR`). Experiment with `O_CREAT | O_EXCL` — `open()` fails with `EEXIST` if the file already exists.

### Q5. Continuous File Creation
Create five new files inside an infinite loop, run in the background, and inspect the open descriptors.

```bash
./q5 &
ls -l /proc/<pid>/fd
```

### Q6. Input and Output Using System Calls
Read from `STDIN` and echo to `STDOUT` using only `read()` and `write()` — no `printf`/`scanf`.

### Q7. File Copying
Emulate `cp file1 file2`: read `file1` in chunks and write to `file2`.

```bash
./q7 file1 file2
```

### Q8. Read-Only File Reading
Open a file with `O_RDONLY`, read it line by line, print each line as it is read, and close on EOF.

### Q9. File Information Extraction
Use `stat()` to print:

| Field | `struct stat` member |
|---|---|
| Inode | `st_ino` |
| Number of hard links | `st_nlink` |
| UID / GID | `st_uid` / `st_gid` |
| Size | `st_size` |
| Block size | `st_blksize` |
| Number of blocks | `st_blocks` |
| Last access / modification / change | `st_atime` / `st_mtime` / `st_ctime` |

### Q10. File Write and Seek
Open in read-write mode, write 10 bytes, `lseek()` forward 10 bytes, write another 10 bytes.
- **a.** Print the return value of `lseek()` (new offset).
- **b.** Inspect the hole with `od`:

```bash
od -c file.txt    # the skipped region shows up as \0 bytes
```

### Q11. File Descriptor Duplication and Appending
Open a file, duplicate the descriptor, append through both, and verify the result.
- **a.** `dup()`
- **b.** `dup2()`
- **c.** `fcntl(fd, F_DUPFD, …)`

Both descriptors share the same open file description, so writes land one after the other.

### Q12. Determining the Opening Mode of a File
Use `fcntl(fd, F_GETFL)` and mask with `O_ACCMODE` to report `O_RDONLY`, `O_WRONLY` or `O_RDWR`.

### Q13. Waiting for STDIN Using `select`
Wait up to 10 seconds for input on `STDIN` using `select()`, and print whether data arrived within the timeout.

### Q14. File Type Identification
Take a path from the command line, call `stat()`/`lstat()`, and identify the type using `S_ISREG`, `S_ISDIR`, `S_ISLNK`, `S_ISCHR`, `S_ISBLK`, `S_ISFIFO`, `S_ISSOCK`.

```bash
./q14 /etc/passwd     # regular file
./q14 /dev/tty        # character device
```

### Q15. Displaying User Environment Variables
Print the user's environment variables by iterating over `extern char **environ`.

### Q16. Mandatory Locking
Lock a whole file using `fcntl()` with `struct flock`:
- **a.** Write lock (`F_WRLCK`)
- **b.** Read lock (`F_RDLCK`)

Run two instances simultaneously to observe blocking behaviour.

> Note: true mandatory locking requires the filesystem to be mounted with `-o mand` and the file's setgid bit set with group-execute cleared; recent kernels have removed support, so the demo behaves as advisory locking on most systems.

### Q17. Online Ticket Reservation Simulation
Two programs:
1. `q17_1.c` — create a file and store an initial ticket number.
2. `q17_2.c` — acquire a write lock, read the ticket number, increment it, print the new number, unlock and close.

Run several instances of the second program at once to see the lock serialise access.

### Q18. Record Locking
Create a file with three records. Lock only the record being accessed (using `l_start` / `l_len` in `struct flock`) before reading or modifying it.
- **a.** Write lock
- **b.** Read lock

---

## Part II — Process Management (Q19–Q30)

### Q19. Process States
Put a process into each of these states and confirm with `ps`/`top`:

| State | How | `ps` STAT |
|---|---|---|
| **a.** Running | busy loop | `R` |
| **b.** Sleeping | `sleep()` / blocking `read()` | `S` |
| **c.** Stopped | `Ctrl+Z` or `kill -STOP <pid>` | `T` |

```bash
ps -o pid,stat,cmd -p <pid>
```

### Q20. Printing Parent and Child Process IDs
Call `fork()` and print `getpid()` and `getppid()` from both parent and child.

### Q21. File Writing by Parent and Child
Open a file, `fork()`, and have both processes write to it. Since they share the file offset, output is interleaved rather than overwritten.

### Q22. Creating a Zombie Process
Child exits immediately while the parent sleeps without calling `wait()`. The child shows as `Z` / `<defunct>` in `ps`.

### Q23. Creating an Orphan Process
Parent exits while the child is still running. The child is adopted by `init`/`systemd` (or a subreaper); `getppid()` changes accordingly.

### Q24. Creating and Waiting for Child Processes
Create three children; the parent waits on one specific child using `waitpid(pid, &status, 0)`.

### Q25. Executing an Executable Program
- **a.** Replace the current process image with another program using an `exec` call.
- **b.** Pass command-line arguments to the executed program, e.g. `./a.out name`.

### Q26. Executing `ls -Rl` with Various `exec` Calls
One program per variant:

| Variant | Path lookup | Args form | Custom env |
|---|---|---|---|
| **a.** `execl` | no | list | no |
| **b.** `execlp` | `PATH` | list | no |
| **c.** `execle` | no | list | yes |
| **d.** `execv` | no | vector | no |
| **e.** `execvp` | `PATH` | vector | no |

### Q27. Maximum and Minimum Real-Time Priority
Print the priority range for `SCHED_FIFO` and `SCHED_RR` using `sched_get_priority_max()` and `sched_get_priority_min()` (typically 1–99 on Linux).

### Q28. Determining and Modifying Program Priority
Read the current nice value with `getpriority()`/`nice(0)`, change it with `nice()`, and verify from the shell:

```bash
nice -n 10 ./q28
renice -n 5 -p <pid>
ps -o pid,ni,pri,cmd -p <pid>
```

Lowering the nice value (raising priority) requires `sudo`.

### Q29. Getting and Modifying Scheduling Policy
Get the current policy with `sched_getscheduler()` and switch between `SCHED_OTHER`, `SCHED_FIFO` and `SCHED_RR` with `sched_setscheduler()`. Needs root for real-time policies.

```bash
sudo ./q29
chrt -p <pid>     # verify
```

### Q30. Running a Task at a Specific Time with a Daemon
Create a daemon (`fork()` → parent exits → `setsid()` → `chdir("/")` → `umask(0)` → close standard descriptors) that sleeps until a target time and then runs a script/task.

```bash
./q30 <HH> <MM> <SS>
ps -ef | grep q30     # daemon has no controlling terminal (TTY = ?)
```

---

## Quick Reference Table

| Q | Topic | Key calls |
|---|---|---|
| 1 | Soft link, hard link, FIFO | `symlink`, `link`, `mkfifo`, `mknod` |
| 2 | Background process & `/proc` | `while(1)`, `/proc/<pid>` |
| 3 | Create file, print fd | `creat` |
| 4 | Open existing file, `O_EXCL` | `open` |
| 5 | Infinite file creation | `open`, `/proc/<pid>/fd` |
| 6 | stdin → stdout | `read`, `write` |
| 7 | Copy file | `open`, `read`, `write` |
| 8 | Read line by line | `open`, `read`, `close` |
| 9 | File metadata | `stat` |
| 10 | Seek and holes | `lseek`, `od` |
| 11 | Descriptor duplication | `dup`, `dup2`, `fcntl` |
| 12 | Open mode | `fcntl(F_GETFL)` |
| 13 | Timed stdin wait | `select` |
| 14 | File type | `stat`, `lstat`, `S_IS*` |
| 15 | Environment variables | `environ` |
| 16 | Whole-file locking | `fcntl(F_SETLKW)` |
| 17 | Ticket reservation | `fcntl` write lock |
| 18 | Record locking | `fcntl` with `l_start`/`l_len` |
| 19 | Process states | `ps`, `kill -STOP` |
| 20 | Parent/child PIDs | `fork`, `getpid`, `getppid` |
| 21 | Shared file writes | `fork`, `write` |
| 22 | Zombie | `fork`, no `wait` |
| 23 | Orphan | `fork`, parent exits |
| 24 | Wait for specific child | `waitpid` |
| 25 | Exec a program | `exec*` |
| 26 | `ls -Rl` via exec family | `execl`, `execlp`, `execle`, `execv`, `execvp` |
| 27 | RT priority range | `sched_get_priority_max/min` |
| 28 | Nice value | `nice`, `getpriority` |
| 29 | Scheduling policy | `sched_getscheduler`, `sched_setscheduler` |
| 30 | Daemon at scheduled time | `fork`, `setsid`, `umask`, `chdir` |
