/*
============================================================================
Name : 21a.c
Author : Som Shiv Gupta
Description : Write two programs so that both can communicate by FIFO -Use two way communication. 
Date: 5th Oct, 2023.
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
	const char *path = "fifo";
	
	char data[] = "This sentence is for fifo 2 way communication";
	
	//Create the FIFO
	int fd1 = mkfifo(path, 0666);
	if(fd1 == -1) {
		perror("Fifo not Generated");
		exit(EXIT_FAILURE);
	}
	
	int open_fifo = open(path, O_RDWR);
	 
	if(open_fifo == -1) {
		perror("Fifo not Opened");
		exit(EXIT_FAILURE);
	}
	
	int data_written = write(open_fifo, data, sizeof(data));
	if(data_written == -1) {
		perror("Writing in FIFO not happen");
	}
	
	int data_read = read(open_fifo, data, sizeof(data));
	if(data_read == -1) {
		perror("Reading in FIFO not happen");
	}
	
	printf("Data read from FIFO: %s\n", data);
	close(open_fifo);
}
