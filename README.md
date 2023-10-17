# PIPEX 42 Project

This project aims to emulate the bash pipe,

```
  < infile command1 | command2 > outfile
```

which runs command1 on infile, uses its output as input for command2, whose output will then be printed to outfile.

In order to imitate this in a C program, we will need a few functions we have not used before.

## Functions:

### execve

```
  int execve(char *path, char **arguments, char **environment)
```

The **execve** C function takes 3 arguments:
  
  1. char *path: The path to the command you want to execute. (cat -> /usr/bin/cat);
  2. char **arguments: An array of arguments for your command (cat -e -> arguments[0] = "cat", arguments[1] = "-e");
  3. char **environment: The environment array, we will get to that later.

execve kills the current process, for example in this code snippet:

```
  execve("/usr/bin/ls", args, env);
  printf("Hello World");
  return (0);
```

The second line will never be executed, since the program is being redirected to the shell, which is why we will need the next function.

### fork

```
  int fork(); 
```

The **fork** C function duplicates the current process into a child process. Its return value is a process ID.

The child's process ID will always be 0, the parent's != 0, which allows to differentiate them and make them do different things.

Using this, we will be able to call a bash command from a child process without terminating the parent.

### pipe

```
  int pipe(int fd[2]);
```

The **pipe** C function takes an array of 2 integers as a parameter and allocates 2 file descriptors to each of its indexes.
fd[0] is called the reading end of the pipe, fd [1] is the writing end.

This pipe allows communication between two different processes, with one of them printing to an end of the pipe, and the other one
reading from the other end.

This is what we will use to replicate the behavior of the bash pipe.

### dup2

```
  int dup2(int fd1, int fd2)
```

The **dup2** C function takes 2 file descriptors as arguments and redirects fd2 to fd1:

```
  int fd = open(file_path, O_WRONLY);
  dup2(fd, STDOUT_FILENO);
  printf("Hello World");
```

Here we swapped the standard output with the file descriptor of "file_path", therefore printf will print to that file instead of the terminal.

### access

```
  int access(char *path, flags);
```

The **access** C function checks the access rights of our program to **path**. It returns -1 when permission is denied, 0 when it is granted.

Here we will use it to find the path to the command that we want to use, specifically with the flag X_OK (check for execute rights).










