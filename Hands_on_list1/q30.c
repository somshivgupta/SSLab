/*
==============================================================================
Name : 30.c
Author : Som Shiv Gupta
Roll No. : MT2023015
Description : Write a program to run a script at a specific time using a 
              Daemon process.
Date: 10 September 2023
==============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(void) {
  int pid;
  if((pid=fork()) < 0) {
    perror("fork");
    exit(-1);
  } 
  
  else if(pid > 0) {
    printf("Child's pid = %d\n", getpid());
    exit(0);
  }
  
  setsid();
  umask(0);
  chdir("/");
  FILE *file = fopen("daemon.txt", "w+");
  
  while(1) {
    fprintf(file, "daemon process...\n");
    fflush(file);
  }
  fclose(file);
}
