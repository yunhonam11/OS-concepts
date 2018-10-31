//	Author: Yunho Nam
//
// 	multipipe.c
//	
//	This program demonstrates the use of multiple pipes
//	for multiple processes all created and running at 
//	the same time. 
//
//	Its first/parent process will create all of the 
//	necessary child processes to partition the tasks 
//	per process.
//
//	The program is designed so that a child process
//	does not create another child process. 
//	All the output of each child process is passed to
//	the parent process using a multipipe array.
//
//	This program serves only to illustrate concurrent
//	multi-process programming using a multipipe, so 
//	its only task is to print the names of all the input
//	files with the characters " thread" attached at the 
//	end of each file name.
//	
//	How to use: 
//	gcc -o multipipe multipipe.c
//	./multipipe f1.txt f2.txt f3.txt f4.txt ...
//


#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char*argv[]) 
{
	int i, m, n, fd[argc - 1][2];	// fd = list of pipes
	int pid; 						// process id
	char line[200];					// file name
 	
 	m = 0; // index of current pipe
	for (i = 1; i < argc; i++)
	{
		if (pipe(fd[m]) < 0)
 		{
 			exit(0);
 		}
		if ((pid = fork()) < 0)
		{
			exit(0);
		}

		// break loop to prevent child process from creating 
		// more child processes
		if (pid == 0)		
		{								
			break;
		}
		m++;	// next pipe for parent process to iterate
	}

	if (pid == 0)	// child process
	{
		/*
			Create a new string with " thread" attached
			at the end of the current file name.
		*/
		char *file_mod = malloc(sizeof(argv[i]) + 8);
    	strcpy(file_mod, argv[i]);
    	strcat(file_mod, " thread\0");		

 		close(fd[m][0]);				// close fd[0] for current pipe 
 		write(fd[m][1], file_mod, 200);	// write to fd[0] for current pipe
	} else {	// parent process
		wait(NULL);

		int p;
		// operate on all pipes 
		for (p = 0; p < argc - 1; p++)
		{
			close(fd[p][1]);
			n = read(fd[p][0], line, 200);
			printf("%s\n", line);
		}
	}

 	exit(0) ;
} 