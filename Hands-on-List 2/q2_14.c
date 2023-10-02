/*
============================================================================
Name : 14.c
Author : Som Shiv Gupta
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
Date: 30th Sep, 2023.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(void) {
	int arr[2];
	
	char p[10];
	if(pipe(arr) == -1) {
		perror("pipe");
		exit(1);
	}
	
	write(arr[1], "som_shiv", 9);
	read(arr[0], p, 9);
	
	printf("%s", p);
	printf("\n");
}
