/*
============================================================================
Name : 32b.c
Author : Som Shiv Gupta
Description : Write a program to implement semaphore to protect any critical section.    
b. protect shared memory from concurrent write access 
   
Date: 11th Oct, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<pthread.h>
#include<semaphore.h>

char *shr_mem;
sem_t mut;

void* write_sh(void* temp) {
	char* msg = (char*)temp;
	sem_wait(&mut);
	
	
	strcpy(shr_mem, msg);
	
	sem_post(&mut);
	
	pthread_exit(NULL);
}

int main(void) {
	int shr_mem_id = shmget(1234, 100, IPC_CREAT | 0777);
	if(shr_mem_id == -1) {
		perror("Error while creating shared memory");
		return 0;
	}
	
	shr_mem = shmat(shr_mem_id, NULL, 0);
	
	if(shr_mem == (char *)-1) {
		perror("Error while calling shmat");
		return 0;
	}
	
	sem_init(&mut, 0 ,1);
	
	pthread_t t1, t2;
	char* msg1 = "My name is Som and it is message 1";
	
	pthread_create(&t1, NULL, write_sh, (void*)msg1);
	printf("Content of shared memory: %s\n", shr_mem);
	
	char* msg2 = "My name is Billa and it is message 2";
	
	pthread_create(&t2, NULL, write_sh, (void*)msg2);
	printf("Content of shared memory: %s\n", shr_mem);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	printf("Content of Shared memory: %s\n", shr_mem);
	shmdt(shr_mem);
}
