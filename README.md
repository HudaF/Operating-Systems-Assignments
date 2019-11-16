# Operating Systems Course-work
CS232 Operating Systems Assignments:

## Bash Scripting 
Used bash command line and scripting.
- cleanup.sh: produces error messages, reads from .csv file and displays count, directory operations 
- tictactoe.sh: simulates a 3x3 game between the computer and the user taking turns.
- test passwd.sh: check and validate passwords

## Introduction to System Calls
Used Linux System Calls & C-programming 
- mycat: emulates the behaviour of Linux cat command. 
- mini-shell : prompt display, child and parent processes, multiple commands using &, redirection to file, track of PIDS of working processes, environment variables(Path), cd & pwd, exit after killing child processes.

## Memory Management Routines
Used Free Space Management concepts to implement routines which provided dynamic memory management capabilities to the user.
- initialization and deallocation of memory block using *mmap* and *munmap *.
- **void * my_malloc(int size)**: this function mimics the behaviour of malloc().
- **void my_free (void *)**: this function takes a pointer previouly allocated by
my malloc() and frees it.
- **void * my_calloc(int num, int size)**: this mimics the behaviour of libc calloc() function.
- **void my_realloc (void *  int)**: mimics the behaviour of libc realloc() function.
- **void my_coalesce()**: this coalesces the fragmented free list and is called from time to time to de-fragment the heap.
- **void my_showfreelist()**: this lists all the nodes in the free list.
