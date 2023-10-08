/*
============================================================================
Name : 15.c
Author : Som Shiv Gupta
Description : Write a simple program to send some data from parent to the child process.
Date: 30th Sep, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(void) {
    pid_t childp;
    int p[2];
    
    char *mes = "My name is Som Shiv Gupta and my Roll no. is MT2023015";
    
    int status = pipe(p);
    if(status == -1) {
    	perror("Error while creating an pipe");
    	return 0;
    }
    
    childp = fork();
    if(childp == -1) {
    	perror("Error while creating child");
    	return 0;
    }    	
    
    else if (childp == 0) {
    	char res[100];
	close(p[1]);    	
	int t1 = read(p[0], &res, sizeof(mes));
	if(t1 == -1) {
		perror("Error while reading");
		return 0;
	}
		
	printf("Parent data is: %s\n", mes);
    }
	    
    else {
	close(p[0]);
	int t2 = write(p[1], &mes, strlen(mes));
	if(t2 == -1) {
		perror("Writing Error");
		return 0;  
	}
    }
     
}

