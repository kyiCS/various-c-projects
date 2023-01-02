# Various-C-Projects
By Kelvin Yi

## P2 Program

The program should take the directory name from where to start the file traversal as a command-line argument and print the file hierarchy starting with the directory that is provided by the command-line argument.
If the program is executed without any arguments, the program should print the file hierarchy starting with the current directory where the program is executed. If there are no directories in the current directory only files are listed one per line.
If there are other directories in the current directory then the directory name is first displayed on a separate line and then the files in that directory are listed one-per-line with one-tab indentation.
If a file is a symbolic link then the program should display the symbolic link name and in parentheses the file name the link points to.
The program should also support three command-line options:

-S

This should list all files in the file hierarchy and print the file size next to the filename in parenthesis. 

-s <file size in bytes>

This should list all files in the file hierarchy with file size greater than or equal to the value specified.

-f <string pattern>

This should list all files in the file hierarchy whose file name or directory name contains the substring specified in the string pattern option.

The program should support not only each of these options separately but also any combination of these options. For example: -S, -s 1024, -f jpg, -S -s 1024, -S -f jpg, -s 1024 -f jpg, -S -s 1024 -f jpg, -S -f jpg -s 1024.
If both -s and -f options are specified then the program should list only those files that match both criteria. The order of the options should not matter.

### Getting Started with P2:

The libraries used in this program are:
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

To run this program, go to Vulcan.
Compile the program to produce an output file: gcc -o p2.o p2.c
To run this program, use the command: ./p2.o
Additional commands: -S, -f (long),-s (string)
To run with -S: ./p2.o -S

***************

## P3 Program
A simple shell or command line interpreter written in C-90.

### Getting Started with P3:

This program was compiled using Vulcan.
To compile, use the command: gcc -o p3.o p3.c
This will create an output file named p3.o.
Run this output file with the command: ./p3.o
This will take you into the shell.

How to use the shell:

A shell prompt will appear while you are in the shell.
The user is able to input any UNIX command into the shell.

Custom internal commands are also available.
This includes:
help
cd <direnctory>
exit

***************

## P4 Program
P4 is an extension of P3 that adds additional functionality.

The simple shell program should intercept Control-C and Control-Z characters and perform the appropriate action on the child process instead of the parent process (i.e., interrupt the child process instead of interrupting the parent process when Control-C is entered and stop/suspend the child process instead of stopping the parent process when Control-Z is entered). You should print a message saying the child process has been interrupted or stopped.
The shell program should support I/O redirection for both standard input and standard output. For example: ./myprog arg1 arg2 < inputfile > outputfile.  The program myprog with command-line arguments arg1 and arg2, uses inputfile file for standard input file stream and sends standard output file stream to the file outputfile. If the file outputfile does not exist, a new file should be created and if the file outputfile exists, it should be over-written. You can assume that white space will serve as the delimiter for the I/O redirection symbols < and >.
Implement the following internal commands:

jobs - lists the processes along with their corresponding process id that were stopped when the user enters Control-Z. Whenever the user enters the Control-Z character, the simple shell program must keep track of processes that are stopped and the jobs command should list such processes.
continue <pid> - sends the continue signal to the process with process id <pid>. You can obtain the <pid> to send the continue signal using the jobs commands.

### Getting Started with P4:
Use the command: gcc -o p4.o p4.c
start the shell with: ./p4.o
