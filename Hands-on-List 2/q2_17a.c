/*
============================================================================
Name : 17a.c
Author : Som Shiv Gupta
Description : Write a program to execute ls -l | wc.
a. use dup
Date: 1st October, 2023.
============================================================================
*/

#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>

void main() {
	int p[2];
	int status;
	pid_t childP;
	
	status  = pipe(p);
	
	if(status == -1) 
		perror("Error while creating the file");
	
	else {
		childP = fork();
		
		if(childP == -1)
			perror("Error while creating the file");
		
		else if(childP == 0) {
			close(STDIN_FILENO);
			dup(p[0]);
			close(p[1]);
			execl("usr/bin/wc", "wc", NULL);
		}
		
		else {
			close(STDOUT_FILENO);
			dup(p[1]);
			close(p[0]);
			execl("usr/bin/ls", "ls", "-l", "-l", NULL);
		}
	}
}
