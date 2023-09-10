/*
==============================================================================
Name : q20.c
Author : Som Shiv Gupta
Roll No. : MT2023015
Description :  Find out the priority of your running program. Modify the priority with nice command
Date: 06 September 2023
==============================================================================
*/
#include<stdio.h>
#include<sys/resource.h>
#include<unistd.h>

int main(void) {
	int curr = getpriority(PRIO_PROCESS, getpid());
	printf("Current Priority of this process is:%d\n", curr);
	
	//Changing the current running process to 14. 
	int new = nice(14);
	printf("Changed Priority of the process is:%d\n", new);
}
