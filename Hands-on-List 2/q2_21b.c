/*
============================================================================
Name : 21b.c
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
	//int temp = open(path, O_CREAT | O_RDWR, 0666);
	
	char write_data[500];
	
	while(1) {
	int open_fifo = open(path, O_RDWR);
	if(open_fifo == -1) {
		perror("Fifo not Opened");
		exit(EXIT_FAILURE);
	}
	
	int data_read = read(open_fifo, write_data, sizeof(write_data));
	if(data_read == -1) {
		perror("Reading in FIFO not happen");
		return 0;
	}
	
	printf("Data read from FIFO: %s\n", write_data);
	
	char read_data[] = "This is a response of wrting";
	int data_write = write(open_fifo, read_data, sizeof(read_data));
	if(data_write == -1) {
		perror("Writing in Fifo not happen");
		return 0;
	}
	
	close(open_fifo);
	}
}
