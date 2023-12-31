/*
============================================================================
Name : 25.c
Author : Som Shiv Gupta

Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv

Date: 8th Oct, 2023.
============================================================================
*/
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

int main(void) {
	int key = ftok(".", 1);
	int msg_queue = msgget(key, 0744 | IPC_CREAT);
	if(msg_queue == -1) {
		perror("Error generated by calling msgget");
		return 0;
	}
	
	struct msqid_ds info;
	
	int ms_gen = msgctl(msg_queue, IPC_STAT, &info);
	if(ms_gen == -1) {
		perror("Error generated by calling msgctl");
		return 0;
	}
	
	printf("Access permission: %d\n", info.msg_perm.mode);
	printf("UID: %d\t GID: %d\n", info.msg_perm.uid, info.msg_perm.gid);
	printf("Time of last message sent is: %ld\n", info.msg_stime);
	printf("Time of last message received is: %ld\n", info.msg_rtime);
	printf("Time of last change in the message queue: %ld\n", info.msg_ctime);
	printf("Size of Queue is: %ld\n", info.__msg_cbytes);
	printf("Number of message in the queue is: %ld\n", info.msg_qnum);
	printf("Maximum number of bytes allowed is: %ld\n", info.msg_qbytes);
	printf("Pid of the msgsnd: %d\n", info.msg_lspid);
	printf("Pid of the msgrcv: %d\n", info.msg_lrpid);
	
	}
	
