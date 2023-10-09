/*
============================================================================
Name : 31b.c
Author : Som Shiv Gupta
Description : Write a program to create a semaphore and initialize value to the semaphore.    
b. create a counting semaphore     
Date: 9th Oct, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>

int main(void) {
	sem_t bin_sem;
	
	int bin = sem_init(&bin_sem, 0, 5);
	if(bin == -1) {
		perror("Error while using sem_init");
		return 0;
	}
	
	printf("Binary Semaphore Created and Initialized with an initial value of 5\n");
	
}
