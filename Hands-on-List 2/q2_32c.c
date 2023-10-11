/*
============================================================================
Name : 32c.c
Author : Som Shiv Gupta
Description : Write a program to implement semaphore to protect any critical section.    
c. protect multiple pseudo resources ( may be two) using counting semaphore
   
Date: 11th Oct, 2023.
============================================================================
*/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

int res[2];
sem_t sema;

void* pseudo_resource(void* temp) {
	int res_id = *(int*)temp;
	
	sem_wait(&sema);
	
	res[res_id] = 0;
	
	sem_post(&sema);
	
	pthread_exit(NULL);
}

int main(void) {
	pthread_t t[2];
	
	sem_init(&sema, 0, 2);
	
	for(int i = 0; i < 2; i++) {
		res[i] = 1;
		pthread_create(&t[i], NULL, pseudo_resource, (void*)&i);
	}
	
	for(int i = 0; i < 2; i++)
		pthread_join(t[i], NULL);
	
	sem_destroy(&sema);
}
