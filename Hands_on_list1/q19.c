/*
==============================================================================
Name : q19.c
Author : Som Shiv Gupta
Roll No. : MT2023015
Description : Write a program to find out time taken to execute getpid system call. Use time stamp counter.

Date: 26 Augest 2023
==============================================================================
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main(void){
   clock_t t1;
   t1 = clock();
   float ans1 = (float)t1/CLOCKS_PER_SEC;
   printf("Start time is %f\n",ans1);
   
   int pid = getpid();
   t1 = clock();
   float ans2 = (float)t1/CLOCKS_PER_SEC;
   printf("End time is : %f\n",ans2);
   
   float f_ans = ans2 - ans1;
   printf("Total Time Taken is %f\n",f_ans);
}
