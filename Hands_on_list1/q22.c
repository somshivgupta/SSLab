/*
==============================================================================
Name : q22.c
Author : Som Shiv Gupta
Roll No. : MT2023015
Description : Write a program, open a file, call fork, and then write to the file by both the child as well as the parent processes. Check output of the file.
Date: 06 September 2023
==============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdlib.h>

int main(void) {
	int fd = open("q22_file.txt", O_CREAT|O_RDWR, 0777);
	if(fd == -1) {
		perror("file opening have some problem");
		exit(0);
	}
	
	int pid = fork();
	
	if(pid == 0) {
		char str[12] = "How_Are_You";
		int w = write(fd, &str, sizeof(str));
	} 
	
	else {
		char str2[14] = "MynameisBilla";
		int w = write(fd, &str2, sizeof(str2));
		//wait(NULL);
	}
}
	
