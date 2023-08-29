#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>

int main(int argc, char *argv[]) {
	if(argc < 2){
		printf("No argument passed through command line.\n");
	}
	
	struct stat fileinfo;
	int t = stat(argv[1], &fileinfo);
	if(t == -1) {
		perror("Error");
		return 1;
	}
	
	int mode = fileinfo.st_mode;
	if(S_ISREG(mode))
		printf("It is an Regular File\n");
	else if(S_ISDIR(mode))
		printf("It is an Directory\n");
	else if(S_ISBLK(mode))
		printf("It is an Block File\n");
	else if(S_ISCHR(mode))
		printf("It is an Character special file\n");
	else if(S_ISFIFO(mode))
		printf("It is an FIFO special file\n");
	else if(S_ISLNK(mode))
		printf("It is an symbolic link\n");
	 
	return 0;
}
	
