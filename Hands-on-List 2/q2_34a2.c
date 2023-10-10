/*
============================================================================
Name : 34a2.c
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

int main(void)
{
    char data[100];

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
        if (connectionfd== -1) {
            perror("Error while accepting a connection!");
            return 0;
        }

        if (fork() == 0)
        {
                // Child
            int writeBytes = write(connectionfd, "I'm the server!", 15);
            if (writeBytes == -1) {
                 perror("Error while writing to network via socket!");
                 return 0;
            }
                 
            printf("Data sent to client!\n");

            int readBytes = read(connectionfd, data, 100);
            if (readBytes == -1) {
                perror("Error while reading from network via socket!");
                return 0;
            }
                
            printf("Data from client: %s\n", data);
        }
            
       else
       {
            // Parent
            close(connectionfd);
       }

    }

    close(socketfd);
}
