*
============================================================================
Name : 18.c
Author : Som Shiv Gupta
Description : Write a program to find out total number of directories on the pwd. execute ls -l | grep ^d | wc ? Use only dup2
Date: 3rd Oct, 2023.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(void) {
	int p1[2], p2[2];
	pid_t childp1, childp2;
	
	int status1 = pipe(p1);
	int status2 = pipe(p2);
	
	if(status1 == -1 || status2 == -1)
		perror("Pipe not created");
	
	else {
		childp1 = fork();
		
		if(childp1 == -1)
			perror("Child not created");
		
		else if(childp1 == 0) {
			close(p1[0]);
			close(p1[1]);
			close(p2[1]);
			
			close(STDIN_FILENO);
			dup2(p2[0], STDIN_FILENO);
			
			execl("/usr/bin/wc", "wc", NULL);
		}
		
		else {
			childp2 = fork();
			
			if(childp2 == -1)
				perror("Child not created");
			
			else if(childp2 == 0) {
				close(p1[1]);
				close(p2[0]);
				
				close(STDIN_FILENO);
				dup2(p1[0], STDIN_FILENO);
				close(STDOUT_FILENO);
				dup2(p2[1], STDOUT_FILENO);
				
				execl("/usr/bin/grep", "grep ^d", "^d", NULL);
			}
			
			else {
				close(p1[0]);
				close(p2[1]);
				close(p2[0]);
				
				close(STDOUT_FILENO);
				dup2(p1[1], STDOUT_FILENO);
				
				execl("/usr/bin/ls", "ls", "-l", "-l", NULL);
			}
		}
	}
}
