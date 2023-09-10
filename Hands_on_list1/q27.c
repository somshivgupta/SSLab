/*
==============================================================================
Name : q27.c
Author : Som Shiv Gupta
Roll No. : MT2023015
Description : Write a program to execute ls -Rl by the following system calls
	a. execl
	b. execlp
	c. execle
	d. execv
        e. execvp
Date: 08 September 2023
==============================================================================
*/
#include<stdio.h>
#include<unistd.h>

int main(void) {
	int choice;
	printf("Choose 1 for execl system call\n");
	printf("Choose 2 for execlp system call\n");
	printf("Choose 3 for execle system call\n");
	printf("Choose 4 for execv system call\n");
	printf("Choose 5 for execvp system call\n");
	
	scanf("%d", &choice);
	
	if(choice == 1) {
		printf("Execution of execl system call\n");
		execl("/bin/ls", "ls", "-Rl", (char *)0);
	}
	
	else if(choice == 2) {
		printf("Execution of execlp system call\n");
		execlp("ls", "ls", "-Rl", (char *)0);
	}
	
	else if(choice == 3) {
		printf("Execution of execle system call\n");
		execle("/bin/ls", "-R", "-l", NULL, NULL);
	}
	
	else if(choice == 4) {
		printf("Execution of execv system call\n");
		static char *argv[] = {"/bin/ls", "-Rl", NULL};
		execv(argv[0], argv);
	}
	
	else if(choice == 5) {
		printf("Execution of execvp system call\n");
		static char *argv[] = {"/bin/ls", "-Rl", NULL};
		execvp(argv[0], argv);
	}
	
	else {
		printf("You Have Chossen an Wrong Number\n");
	}
}
	
