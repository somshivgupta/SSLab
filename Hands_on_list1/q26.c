/*
============================================================================
Name : q26.c
Author : Som Shiv Gupta
Roll no: MT2023015
Description :Write a program to execute an executable program.
             a. use some executable program
             b. pass some input to an executable program. (for example execute an executable of $./a.out name)
Date:  9th September 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main(void) {
    char inp[100];
    printf("Enter the input: ");
    scanf("%s",inp);
    char f[10] ="./q24 ";
    strcat(f,inp);
    int status  = system(f);
    if(status < 0) {
    	perror("file");
    	exit(-1);
    }
}
