/*
==============================================================================
Name : q25.c
Author : Som Shiv Gupta
Roll No. : MT2023015
Description :  Write a program to create three child processes. The parent should wait for a particular child (use
waitpid system call).
Date: 07 September 2023
==============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(void){
	int c1;
	c1=fork();
	
	int status;

	if(c1==0){
		printf("Chlid1 pid %d\n", getpid());
		printf("Chlid1 Parent Process_id is %d\n", getppid());

	}

	else{
		int c2;
		c2 = fork();
		if(c2==0){
			printf("Chlid2 pid is %d\n", getpid());
			printf("Chlid2 parent Process_id is %d\n", getppid());
		}
		else{
			int c3;
			c3 = fork();
			if(c3==0){
				sleep(10);
				printf("Chlid3 is %d\n", getpid());
				printf("Child3 Parent Process_id is %d\n", getppid());
			}
			else{
				waitpid(c3,&status,0);
				printf("Parent Process_id %d\n", getpid());
			}

		}
	}
}
