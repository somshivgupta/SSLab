/*
============================================================================
Name : 28.c
Author : Som Shiv Gupta
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
Date: 8th Oct, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct msg_buf {
	long msg_type;
	char msg_text[100];
}msg;

int main(void) {
	int key = ftok(".", 1);
	if(key == -1) {
		perror("Error occured while calling ftok");
		return 0;
	}
	
	int msg_que = msgget(key, 0777 | IPC_CREAT);
	if(msg_que == -1) {
		perror("Error occured while calling msgget");
		return 0;
	}
	
	struct msqid_ds msg_ds;
	int t = msgctl(msg_que, IPC_STAT, &msg_ds);
	if(t == -1) {
		perror("Error occured while calling msgctl");
		return 0;
	}
	
	printf("The current permission is: %o\n", msg_ds.msg_perm.mode);
	
	msg_ds.msg_perm.mode = 0666;
	
	t = msgctl(msg_que, IPC_SET, &msg_ds);
	if(t == -1) {
		perror("Error occured while calling msgctl");
		return 0;
	}
	
	printf("The permission changed to %o\n", msg_ds.msg_perm.mode);

}
	
