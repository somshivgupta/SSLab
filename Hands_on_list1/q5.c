#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main() {
	while(1) {
		int file_desprictor_1 = open("Abhi2",O_CREAT);
		int file_desprictor_2 = open("Jay2",O_CREAT);
		int file_desprictor_3 = open("Shubham2",O_CREAT);
		int file_desprictor_4 = open("Ashutosh2",O_CREAT);
		int file_desprictor_5 = open("Manan2",O_CREAT);
	
		printf("File Desprictor 1 value is %d\n", file_desprictor_1);
		printf("File Desprictor 2 value is %d\n", file_desprictor_2);
		printf("File Desprictor 3 value is %d\n", file_desprictor_3);
		printf("File Desprictor 4 value is %d\n", file_desprictor_4);
		printf("File Desprictor 5 value is %d\n", file_desprictor_5);
		
		if(file_desprictor_1 == -1) {
			perror("File not generated");
			break;
		}
			
		if(file_desprictor_2 == -1) {
			perror("File not generated");
			break;
		}
		
		if(file_desprictor_3 == -1) {
			perror("File not generated");
			break;
		}
		
		if(file_desprictor_4 == -1) {
			perror("File not generated");
			break;
		}
			
		if(file_desprictor_5 == -1) {
			perror("File not generated");
			break;
		}

	}
	
	return 0;
	
}
	
