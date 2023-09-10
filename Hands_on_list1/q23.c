/*
==============================================================================
Name : q23.c
Author : Som Shiv Gupta
Roll No. : MT2023015
Description : Write a program to create a Zombie state of the running program.

Date: 06 September 2023
==============================================================================
*/
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main(void) {
	int process_id = fork();
	
	if(process_id == 0) {
		printf("Exit the child process first to treat it as zombiee\n");
		printf("Child process id: %d\n", getpid());
		exit(0);
		//Use ps <Child Process id> while parent is in sleep then you will get State as zombiee
	}
	
	else {
		printf("Put the Parent process to sleep\n");
		printf("Parent process id: %d\n", getpid());
		//While parent process is in sleep use top system call to check zombiee process 
		sleep(30);
		printf("Parent is now available\n");
	}
}
