/*
============================================================================
Name : 20b.c
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
	char data[500];
	
	int open_fifo = open(path, O_RDONLY);
	if(open_fifo == -1) {
		perror("Fifo not Opened");
		return 0;
	}
	
	int read_data = read(open_fifo, data, sizeof(data));
	if(read_data == -1) {
		perror("Reading in FIFO not happen");
		return 0;
	}
	 
	printf("Data read from FIFO is %s\n", data);
	
	close(open_fifo);
}
