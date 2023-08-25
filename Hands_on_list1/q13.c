#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/select.h>

int main(void) {
	
	struct timeval timeout;
	fd_set read_file;
	
	printf("Enter the Input: ");
	fflush(stdout);
	
	FD_ZERO(&read_file);
	FD_SET(0, &read_file);
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	
	int s = select(1, &read_file, NULL, NULL, &timeout);
	if(s == -1) 
		printf("Error, Something went wrong\n");
	
	else if(s == 0) 
		printf("Data not available\n");
	else
		printf("Data is Available\n");
	close(s);
}
		 
