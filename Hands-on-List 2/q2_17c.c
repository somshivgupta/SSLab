/*
============================================================================
Name : 17a.c
Author : Som Shiv Gupta
Description : Write a program to execute ls -l | wc.
c. use fcntl
Date: 1st October, 2023.
============================================================================
*/

#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<fcntl.h>

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
			fcntl(p[0], F_DUPFD, STDIN_FILENO);
			close(p[1]);
			execl("usr/bin/wc", "wc", NULL);
		}
		
		else {
			close(STDOUT_FILENO);
			fcntl(p[1], F_DUPFD, STDOUT_FILENO);
			close(p[0]);
			execl("usr/bin/ls", "ls", "-l", "-l", NULL);
		}
	}
}
