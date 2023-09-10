/*
==============================================================================
Name : q28.c
Author : Som Shiv Gupta
Roll No. : MT2023015
Description :  Write a program to get maximum and minimum real time priority.
Date: 08 September 2023
==============================================================================
*/
#include<stdio.h>
#include<sched.h>

int main(void) {
	int mini, maxi;
	
	mini = sched_get_priority_min(SCHED_RR);
	maxi = sched_get_priority_max(SCHED_RR);
	
	printf("Minimum real-time Priority will be: %d\n", mini);
	printf("Maximum real-time Priority will be: %d\n", maxi);
}
