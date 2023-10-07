/*
============================================================================
Name : 22.c
Author : Som Shiv Gupta
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO. 
Date: 7th Oct, 2023.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/time.h>
#include<sys/stat.h>
#include<sys/select.h>

int main(void) {
	fd_set fd;
	struct timeval tv;
	
	const char *path = "fifo";
	
	int temp = mkfifo(path, 0666);
	
	int fs = open(path, O_RDONLY);
	if(fs == -1) {
		perror("file not open");
		return 0;
	}
	
	printf("Waiting for data in FIFO (up to 10 seconds)\n");
	
	FD_ZERO(&fd);
	FD_SET(fs, &fd);
	
	tv.tv_sec = 10;
	tv.tv_usec = 0;
	
	int retval = select(1, &fd, NULL, NULL, &tv);
	
	if(retval == -1) {
		printf("select system call executed\n");
		return 0;
	}
	
	else if(retval) {
		printf("Data is received within 10 second\n");
	}
	
	else {
		printf("Data is not received within 10 second\n");
		return 0;
	}
}
