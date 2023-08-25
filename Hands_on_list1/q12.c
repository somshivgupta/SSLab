#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(void) {
	int fd = open("ques12_file.txt", O_CREAT);
	int mode = fcntl(fd, F_GETFL);
	if(mode == -1) {
		perror("Something went wrong");
		return 1;
	}
	
	if(mode == 32768) 
		printf("The Access mode of the file is O_RDONLY(Read Only)\n");
	
	else if(mode == 32769)
		printf("The Access mode of the file is O_WRONLY(Write Only)\n");
	
	else 
		printf("The Access mode of the file is O_RDWR(Read Write)\n");
		
}
