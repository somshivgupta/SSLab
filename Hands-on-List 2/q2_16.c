/*
============================================================================
Name : 16.c
Author : Som Shiv Gupta
Description : Write a program to send and receive data from parent to child vice versa. Use two way communication
Date: 1st October, 2023.
============================================================================
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h>
     
int main(void) 
{
	
    int par_to_child[2];           /* pipe from parent to child */ 
    int child_to_par[2];           /* pipe from child to parent */ 
    pid_t child;                     /* child's PID */ 
    
    int r, w;
    char *writeBuffer, *readBuffer;
         
    /* Create the pipes. */ 
    pipe(par_to_child); 
    pipe(child_to_par); 
     
    /* Create the child process */ 
    child = fork(); 
     
    /* Run the parent's code */ 
    if (child != 0) { 
            /* parent */ 
            close(par_to_child[0]);
            close(child_to_par[1]);
            
            writeBuffer = "It is an parent process";
            w = write(par_to_child[1], &writeBuffer, sizeof(writeBuffer));
            
            if(w == -1)
            	perror("Error while writing from parent to child");
            	
            r = read(child_to_par[0], &readBuffer, sizeof(readBuffer));
            
            if(r == -1)
            	perror("Error while reading from child to parent");
            else 
            	printf("This child said: %s\n", readBuffer);
        } 
        
        else { 
            /* child */ 
            close(par_to_child[1]);
            close(child_to_par[0]);
            
            writeBuffer = "It is an child process";
            w = write(child_to_par[1], &writeBuffer, sizeof(writeBuffer));
            
            if(w == -1)
            	perror("Error while writing to child to parent");
            
            r = read(par_to_child[0], &readBuffer, sizeof(readBuffer));
            if(r == -1)
            	perror("Error while reading from parent to child");
            
            else
            	printf("The Parent said: %s\n", readBuffer);
      }
} 
