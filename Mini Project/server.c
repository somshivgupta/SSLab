#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>
#include<sys/socket.h>
#include<netinet/in.h>

#include "./Mini_Project/head.h"
#include "./Mini_Project/details.h"

void connection_handler(int cli_soc) {
	char readb[1000], writeb[1000];
	int choice;
	
	int write_b = write(cli_soc, HEADING, sizeof(HEADING));
	if(write_b == -1) {
		perror("Error while performing write function\n");
		return;
	}
	
	int read_b = read(cli_soc, readb, sizeof(readb));
	if(read_b == -1) {
		perror("Error while performing read function\n");
		return;
	}
	
	choice = atoi(readb);
	switch(choice) {
		case 1:
			//Admin
			admin_details(cli_soc);
			break;
		
		case 2:
			//Professor
			prof_details(cli_soc);
			break;
		
		case 3:
			//Student
			//stud_details(cli_soc);
			break;	 
		default:
			printf("Your Have Entered the wrong choice\n");
	}
		
}

int main(void){
	int ser_soc = socket(AF_INET, SOCK_STREAM, 0); 
	if(ser_soc == -1) {
		perror("Error while running socket");
		return 0;
	}
	
	struct sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(8339);
	ser.sin_addr.s_addr = INADDR_ANY;
	
	printf("Server Side: Socket Created Successfully\n");
	
	int t = 1;
	int re_use = setsockopt(ser_soc, SOL_SOCKET, SO_REUSEADDR, &(t), sizeof(t));
	
	if(re_use == -1) {
		perror("Error while using same port number\n");
		return 0;
	}
	
	int bn = bind(ser_soc, (struct sockaddr *)&ser, sizeof(ser));
	if(bn == -1) {
		perror("Error while calling bind\n");
		return 0;
	}
	printf("Binding to socket is successful\n");
	
	int ls = listen(ser_soc, 10);
	if(ls == -1) {
		perror("Error while calling listen");
		close(ser_soc);
		return 0;
	}
	
	int port = ntohs(ser.sin_port);
        printf("Server is running on port %d\n", port);
	
	int cli_soc;
	while(1) {
		cli_soc = accept(ser_soc, NULL, NULL);
		if(cli_soc == -1) {
			perror("Error while calling accept\n");
			close(ser_soc);
		}
		
		else {
			if(!fork()) {
				connection_handler(cli_soc);
				close(cli_soc);
				return 0;
			}
		}
	}
	
	close(ser_soc);
}
