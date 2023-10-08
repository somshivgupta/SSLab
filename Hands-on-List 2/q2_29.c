/*
============================================================================
Name : 29.c
Author : Som Shiv Gupta
Description : Write a program to remove the message queue
Date: 8th Oct, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void) {
   
    int key = ftok(".", 1);
    if(key == -1) {
    	perror("Error occured while running ftok");
    	return 0;
    }

    int msgid = msgget(key, 0666 | IPC_CREAT);
    if(msgid == -1) {
    	perror("Error occured while running msgget");
    	return 0;
    }
    
    printf("Message queue id = %d\n", msgid);


    int ctr = msgctl(msgid, IPC_RMID, NULL);
    if(ctr == -1) {
        perror("Error while calling msgctl");
        return 0;
    }

    printf("Message queue removed.\n");
}
