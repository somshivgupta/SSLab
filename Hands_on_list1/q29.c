/*
==============================================================================
Name : q29.c
Author : Som Shiv Gupta
Roll No. : MT2023015
Description :  Write a program to get scheduling policy and modify the 
              scheduling policy (SCHED_FIFO, SCHED_RR).
Date: 08 September 2023
==============================================================================
*/

#include<stdio.h>
#include<sched.h>
#include<stdlib.h>
#include<unistd.h>

int main(void) {
  int curr =sched_getscheduler(getpid());
  printf("Scheduling Policy = %d\n\n", curr);
  struct sched_param sp = {.sched_priority=20};

  printf("Changing the scheduling policy to FIFO...\n");
  int next = sched_setscheduler(0, SCHED_FIFO, &sp);
  if (next == -1) {
    perror("sched_setscheduler");
    exit(0);
  }
  
  curr = sched_getscheduler(getpid());
  printf("Scheduling Policy = %d\n", curr);
  printf("\n");
  
  printf("Changing the scheduling policy to RR...\n");
  next = sched_setscheduler(0, SCHED_RR, &sp);
  if (next == -1) {
    perror("sched_setscheduler");
    exit(0);
  }
  curr = sched_getscheduler(getpid());
  printf("Scheduling Policy = %d\n", curr);
}
