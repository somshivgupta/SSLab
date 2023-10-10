#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(void) {
	char msg[100];
	int cli_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(cli_sock == -1) {
		perror("Error occured while calling socket");
		return 0;
	}
	
	struct sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(1284);
	ser.sin_addr.s_addr = INADDR_ANY;
	
	int cnt = connect(cli_sock, (struct sockaddr *)&ser, sizeof(ser));
	
	if(cnt == -1) {
		perror("Error while generating connection");
		return 0;
	}
	
	//memset(msg, 0, sizeof(msg));
	
	int rec = recv(cli_sock, msg, sizeof(msg), 0);
	if(rec == -1) {
		perror("Error while receving the data");
		return 0;
	}
	
	printf("Received message from server %s\n", msg);
	
	while(1) {
		memset(msg, 0, sizeof(msg));
		fgets(msg, sizeof(msg), stdin);
		send(cli_sock, msg, strlen(msg), 0);
		if(strcmp(msg, "exit\n") == 0) {
			printf("Closing the connection.\n");
			break;
		}
	}
	
	close(cli_sock);
} 
