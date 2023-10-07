/*
============================================================================
Name : 20a.c
Author : Som Shiv Gupta
Description : Write two programs so that both can communicate by FIFO -Use one way communication. 
Date: 4th Oct, 2023.
============================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void) {
	const char *path = "./q2_20";
	char data[] = "Hello my name is Som Shiv, and It is code for Fifo communication";
	
	//Create the FIFO
	int fd = mkfifo(path, 0666);
	if(fd == -1) {
		perror("Fifo not Generated");
		exit(EXIT_FAILURE);
	}
	
	int open_fifo = open(path, O_WRONLY);
	if(open_fifo == -1) {
		perror("Fifo not Opened");
		exit(EXIT_FAILURE);
	}
	
	int data_written = write(open_fifo, data, sizeof(data));
	if(data_written == -1) {
		perror("Writing in FIFO not happen");
	}
	
	close(open_fifo);
}
