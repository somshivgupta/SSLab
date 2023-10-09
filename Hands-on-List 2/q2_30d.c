/*
============================================================================
Name : 30d.c
Author : Som Shiv Gupta
Description : Write a program to create a shared memory.
d. remove the shared memory
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
	printf("Data: %s\n", data);
	
	int det = shmctl(sh_mem, IPC_RMID, NULL);
	if(det == -1) {
		perror("Shared Memory not Removed");
		return 0;
	}
	
	printf("Shared Memory is Removed\n");
}
