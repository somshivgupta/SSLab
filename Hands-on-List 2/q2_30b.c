/*
============================================================================
Name : 30b.c
Author : Som Shiv Gupta
Description : Write a program to create a shared memory.
b. attach with O_RDONLY and check whether you are able to overwrite.
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
	
	int sh_mem = shmget(key, 1024, IPC_CREAT | 0777);
	if(sh_mem == -1) {
		perror("Error while running shmget");
		return 0;
	}
	
	char *data = (char *)shmat(sh_mem, NULL, SHM_RDONLY);
	printf("Shared memory have data is %s\n:", data);
}
