/*
============================================================================
Name : 27a.c
Author : Som Shiv Gupta
Description : Write a program to receive messages from the message queue.
a. with 0 as a flag
Date: 8th Oct, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct msg_buf {
	long msg_type;
	char msg_text[100];
	//= "This code is for receiving message with 0 as a flag";
}msg; 

int main(void) {	
	int key = ftok(".", 1);
	if(key == -1) {
		perror("Error ouccred while calling ftok");
		return 0;
	}
	
	int msg_que = msgget(key, 0666 | IPC_CREAT);
	if(msg_que == -1) {
		perror("Error while running msgget");
		return 0;
	}
	
	msg.msg_type = 1;
	fgets(msg.msg_text, 10, stdin);
	
	//Sending the message
	msgsnd(msg_que, &msg, sizeof(msg), 0); 
	
	//Receiving the msg with 0 as a flag
	int rec = msgrcv(msg_que, &msg, sizeof(msg), 1, 0);
	if(rec == -1) {
		perror("Message not received");
		return 0;
	}
	
	printf("Message Received is %s\n", msg.msg_text);
}
