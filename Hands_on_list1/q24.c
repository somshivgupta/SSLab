/*
==============================================================================
Name : q24.c
Author : Som Shiv Gupta
Roll No. : MT2023015
Description :  Write a program to create an orphan process.
Date: 07 September 2023
==============================================================================
*/
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char * argv[]) {
	printf("%s\n", argv[1]);
	
	int process_id = fork();
	
	if(process_id == 0) {
		printf("Child process id %d\n", getpid());
		sleep(30); 
	}
	
	else {
		 exit(0);
	}
}
