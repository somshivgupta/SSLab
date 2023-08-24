#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {
	FILE *fd;
	char line[1000];
	
	fd = fopen("read_question_8.txt", "r");
	if(fd == NULL)
		return 1;
	
	while(fgets(line, 1000, fd)) {
		printf("%s", line);
	}
	
	fclose(fd);
}
	
