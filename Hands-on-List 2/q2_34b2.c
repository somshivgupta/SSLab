/*
============================================================================
Name : 34b2.c
Author : Som Shiv Gupta
Description : Write a program to create a concurrent server.
b. use pthread_create
Date: 10th Oct, 2023.
============================================================================
*/

#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <stdio.h>      
#include <unistd.h>     
#include <pthread.h>    


void communicate(int *fd)
{
    char data[100];

    int writes = write(*fd, "I'm the server!", 15);
    if (writes == -1) {
        perror("Error while writing to network via socket\n");
        return;
    }
    
    printf("Data sent to client!\n");

    int reads = read(*fd, data, 100);
    if (reads == -1) {
        perror("Error while reading from network via socket!");
        return;
    }
    
    printf("Data from client: %s\n", data);

    close(*fd);
}

int main(void)
{
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1)
    {
        perror("Error while creating socket!");
        return 0;
    }
    printf("Server side socket successfully created!\n");
	
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);

    int binds = bind(socketfd, (struct sockaddr *)&addr, sizeof(addr));
    if (binds == -1)
    {
        perror("Error while binding name to socket!");
        return 0;
    }
    printf("Binding to socket was successful!\n");

    int listens = listen(socketfd, 2);
    if (listens == -1)
    {
        perror("Error while trying to listen for connections!");
        return 0;
    }
    printf("Now listening for connections on a socket!\n");
	
    struct sockaddr_in client;
    while (1)
    {
        int clients = (int)sizeof(client);
        int connectionfd = accept(socketfd, (struct sockaddr *)&client, &clients);
        if (connectionfd == -1) {
            perror("Error while accepting a connection!");
            return 0;
        }
         
        pthread_t t_ID;  
        if (pthread_create(&t_ID, NULL, (void *)communicate, &connectionfd))
                perror("Error while creating thread");
        
    }

    close(socketfd);
}
