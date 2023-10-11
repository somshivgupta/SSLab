/*
============================================================================
Name : 32d.c
Author : Som Shiv Gupta
Description : Write a program to implement semaphore to protect any critical section.    
d. remove the created semaphore
   
Date: 11th Oct, 2023.
============================================================================
*/

#include<stdio.h>
#include<semaphore.h>
#include<sys/sem.h>

sem_t sema;

int main(void) {
	int val;
	
	sem_init(&sema, 0, 1);
	int shr = sem_getvalue(&sema, &val);
	if(shr == -1) {
		perror("Error while running sem_getvalue");
		return 0;
	}
	
	printf("Semaphore Created Successfully: %d\n", val);
	
	int sed = sem_destroy(&sema);
	if(sed == -1) {
		perror("Error while running sem_destroy");
		return 0;
	}
	
	printf("Semaphore destroyed successfully\n");
	
}
