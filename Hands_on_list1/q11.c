#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
	//use of dup and form duplicate in ques_11_1
	int fd1 = open("ques_11_1.txt", O_CREAT|O_RDWR,0777);
	if(fd1 == -1) {
		perror("Original file do not exist\n");
		return -1;
	}
	
	char buf[]="Writting in file name ques_11.txt\t";
	
	write(fd1, buf, sizeof(buf));
	int fd2 = dup(fd1);
	if(fd2 == -1) {
		perror("Duplicate file do not open\n");
		return -1;
	}
	
	char buf2[]="Written in local/duplicate file\n";
	write(fd2, buf2, sizeof(buf2));
	close(fd1);
	
	//fcntl function and duplicate in ques_11_2
	fd1 = open("ques_11_2.txt", O_CREAT|O_RDWR,0777);
	if(fd1 == -1) {
		perror("Original file do not exist\n");
		return -1;
	}
	
	char buf3[] = "Writting in the file named ques_11_2.txt ";
	write(fd1, buf3, sizeof(buf3));
	fd2 = fcntl(fd1, F_DUPFD);
	
	fd2 = dup(fd1);
	if(fd2 == -1) {
		perror("Duplicate file do not open\n");
		return -1;
	}
	
	char buf4[]="Written in local/duplicate in second file\n";
	write(fd2, buf4, sizeof(buf4));
	close(fd1);
	
	//Use of dup2
	fd1 = open("ques_11_3.txt", O_CREAT|O_RDWR,0777);
	if(fd1 == -1) {
		perror("Original file do not exist\n");
		return -1;
	}
	
	char buf1[] = "Writting in the file named ques_11_3.txt ";
	write(fd1, buf1, sizeof(buf1));
	dup2(fd1, 1);
	
	fd2 = dup(fd1);
	if(fd2 == -1) {
		perror("Duplicate file do not open\n");
		return -1;
	}
	
	char buf5[]="Written in local/duplicate in second file\n";
	write(fd2, buf5, sizeof(buf5));
	close(fd1);
}
