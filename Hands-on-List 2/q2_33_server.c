/*
============================================================================
Name : 33_server.c
Author : Som Shiv Gupta
Description : Write a program to communicate between two machines using socket.
Date: 10th Oct, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(void){
	int ser_soc = socket(AF_INET, SOCK_STREAM, 0);
	if(ser_soc == -1) {
		perror("Error while running socket");
		return 0;
	}
	
	struct sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(1284);
	ser.sin_addr.s_addr = INADDR_ANY;
	
	int bn = bind(ser_soc, (struct sockaddr *)&ser, sizeof(ser));
	if(bn == -1) {
		perror("Error while calling bind\n");
		return 0;
	}
	
	int ls = listen(ser_soc, 10);
	/*if(ls == -1) {
		perror("Error while calling listen");
		close(ser_soc);
		return 0;
	}*/
	
	int cli_soc = accept(ser_soc, NULL, NULL);
	if(cli_soc == -1) {
		perror("Error while calling accept\n");
		close(ser_soc);
		close(cli_soc);
		return 0;
	}
	
	char msg[1024];
	char buffer[1024];
	fgets(msg, sizeof(msg), stdin);
	//read(cli_soc, msg, sizeof(msg));
	send(cli_soc, msg, sizeof(msg), 0);
	recv(cli_soc, buffer,sizeof(buffer),0);
	printf("The message received is: %s\n", buffer);
	
	close(ser_soc);
	close(cli_soc);
}
