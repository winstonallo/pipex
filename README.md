# PIPEX 42 Project

This project aims to emulate the bash pipe,

```
< infile command1 | command2 > outfile
```

which runs command1 on infile, uses its output as input for command2, whose output will then be printed to outfile.

In order to imitate this in a C program, we will need a few functions we have not used before.

## Functions:

### pipe

```
int pipe(int fd[2]);
```

The 'pipe' C function takes an array of 2 integers as a parameter and allocates 2 file descriptors to each of its indexes.
fd[0] is called the reading end of the pipe, fd [1] is the writing end.

This pipe allows communication between two different processes, with one of them printing to an end of the pipe, and the other one
reading from the other end.

This is what we will use to replicate the behavior of the bash pipe.

### fork

```
int fork(); 
```

Tho 'fork' C function duplicates the current process into a child process. Its return value is a process ID.

The child's process ID will always be 0, the parent's != 0, which allows to differentiate them and make them do different things.

