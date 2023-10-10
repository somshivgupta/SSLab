/*
============================================================================
Name : 34a1.c
Author : Som Shiv Gupta
Description : Write a program to create a concurrent server.
a. use fork
Date: 10th Oct, 2023.
============================================================================
*/

#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <stdio.h>      
#include <unistd.h>     

int main(void) {  
    char data[100];
     
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1)
    {
        perror("Error while creating socket!");
        return 0;
    }
    
    printf("Client side socket successfully created!\n");

    struct sockaddr_in addr;  

    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);

    int connectStatus = connect(socketfd, (struct sockaddr *)&addr, sizeof(addr));
    if (connectStatus == -1)
    {
        perror("Error while connecting to server!");
        return 0;
    }
    
    printf("Client to serrver connection successfully established!\n");

  
    int readBytes = read(socketfd, data, 100);
    if (readBytes == -1) {
        perror("Error while reading from network via socket!");
        return 0;
    }
    
    printf("Data from server: %s\n", data);

    int writeBytes = write(socketfd, "I'm the client!", 15);
    if (writeBytes == -1) {
        perror("Error while writing to network via socket!");
        return 0;
    }

    printf("Data sent to server!");
    

    close(socketfd);
}
