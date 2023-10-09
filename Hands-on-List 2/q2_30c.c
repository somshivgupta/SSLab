/*
============================================================================
Name : 30c.c
Author : Som Shiv Gupta
Description : Write a program to create a shared memory.
c. detach the shared memory
Date: 8th Oct, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>

int main(void) {
	int key = ftok(".", 1);
	if(key == -1) {
		perror("Error while running ftok");
		return 0;
	}
	
	int sh_mem = shmget(key, 1024, 0777);
	if(sh_mem == -1) {
		perror("Error while running shmget");
		return 0;
	}
	
	char *data = (char *)shmat(sh_mem, (void*)0, 0);
	
	int det = shmdt(data);
	if(det == -1) {
		perror("Detachment not happen sucessfully");
		return 0;
	}
	
	printf("Shared Memory is detached\n");
}
