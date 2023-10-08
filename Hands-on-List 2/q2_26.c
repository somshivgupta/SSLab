/*
============================================================================
Name : 26.c
Author : Som Shiv Gupta
Description : Write a program to send messages to the message queue. Check $ipcs -q
Date: 8th Oct, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct buffer{
	long mtype;
	char mtext[100];
}msg;

int main(void) {
	int key = ftok(".", 1);
	if(key == -1) {
		perror("Error while running ftok");
		return 0;
	}
	
	int msg_que = msgget(key, 0666 | IPC_CREAT);
	if(msg_que == -1) {
		perror("Error while running msgget");
		return 0;
	}
	
	msg.mtype = 1;
	fgets(msg.mtext, 10, stdin);
	int ms = msgsnd(msg_que, &msg, sizeof(msg), 0);
	if(ms == -1) {
		perror("Error while running msgsnd");
		return 0;
	}
	
	printf("Data sent to the message queue\n");
}

