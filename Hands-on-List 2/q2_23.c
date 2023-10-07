/*
============================================================================
Name : 23.c
Author : Som Shiv Gupta
Description : Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer). 
Date: 7th Oct, 2023.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>

int main(void) {
	char *name = "q_23_fifo";
	
	int status = mkfifo(name, S_IRWXU);
	
	if(status == -1) {
		perror("Fifo not genrated");
		return 0;
	}
	
	long max_files = sysconf(_SC_OPEN_MAX);
	if(max_files == -1) {
		perror("Error while calling sysconf");
		return 0;
	}
	
	printf("Maximum number of that can be opened will be: %ld\n", max_files);
	
	long pipe_size = pathconf(name, _PC_PIPE_BUF);
	if(pipe_size == -1) {
		perror("Error while calling pathconf");
		return 0;
	}
	
	printf("Maximum size of the pipe: %ld\n", pipe_size);
}
