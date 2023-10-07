/*
============================================================================
Name : 19.c
Author : Som Shiv Gupta
Description : Create a FIFO file by
a. mknod system call
b. mkfifo library function
Date: 3rd Oct, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(void) {
	
	//Create a FIFO file by mknod system call 
        int fd1 = mknod("mknod_fifo", S_IFIFO | 0666, 0);
	if(fd1 == -1) {
		perror("File not created by mknod");
		return 0;
	}
	
	//Create a FIFO file by mkfifo library function
	int fd2 = mkfifo("mkfifo_fifo", 0666);
	if(fd2 == -1) {
		perror("File not created by mkfifo");
		return 0;
	}
	
}
		
