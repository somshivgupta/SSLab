/*
==============================================================================
Name : q21.c
Author : Som Shiv Gupta
Roll No. : MT2023015
Description : Write a program, call fork and print the parent and child 		process id.
Date: 06 September 2023
==============================================================================
*/
#include<stdio.h>
#include<unistd.h>

int main(void) {
	int pid = fork();
	
	if(pid == 0) 
		printf("Process id of child process is: %d\n", getpid());
	
	else 
		printf("Process id of parent process is: %d\n", getpid());
}
