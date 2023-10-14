#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void connection(int cli_sock) {
	char readb[1000], writeb[1000];
	char extrab[1000];
	int read_Bytes, write_Bytes;
	
	
	do {
		bzero(readb, sizeof(readb));
		bzero(extrab, sizeof(extrab));
			
		read_Bytes = read(cli_sock, readb, sizeof(readb));
		if(read_Bytes == -1) {
			perror("Error while reading the data");
			return;
		}
		
	 	else if (read_Bytes == 0)
            		printf("No error received from server! Closing the connection to the server now!\n");
        	else if (strchr(readb, '^') != NULL)
        	{
            		// Skip read from client
            		strncpy(extrab, readb, strlen(readb) - 1);
            		printf("%s\n", extrab);
		        write_Bytes = write(cli_sock, "^", strlen("^"));
		        if (write_Bytes == -1)
		       {
		        	perror("Error while writing to client socket!");
		        	break;
		       }
		}
		else if (strchr(readb, '$') != NULL)
		{
		    // Server sent an error message and is now closing it's end of the connection
		    strncpy(extrab, readb, strlen(readb) - 2);
		    printf("%s\n", extrab);
		    printf("Closing the connection to the server now!\n");
		    break;
		}
		else
		{
		    bzero(writeb, sizeof(writeb)); // Empty the write buffer

		    if (strchr(readb, '#') != NULL)
		        strcpy(writeb, getpass(readb));
		    else
		    {
		        printf("%s\n", readb);
		        scanf("%[^\n]%*c", writeb); // Take user input!
		    }

		    write_Bytes = write(cli_sock, writeb, strlen(writeb));
		    
		    if (write_Bytes == -1)
		    {
		        perror("Error while writing to client socket!");
		        printf("Closing the connection to the server now!\n");
		        break;
		    }
		}
	}while(read_Bytes > 0);
	       
	close(cli_sock);
}

int main(void) {
	char msg[100];
	int cli_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(cli_sock == -1) {
		perror("Error occured while calling socket");
		return 0;
	}
	
	struct sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(8339);
	ser.sin_addr.s_addr = INADDR_ANY;
	printf("Client Side: Socket created successfully\n");
	
	int t = 1;
	int re_use = setsockopt(cli_sock, SOL_SOCKET, SO_REUSEADDR, &(t), sizeof(t));
	
	if(re_use == -1) {
		perror("Error while using same port number\n");
		return 0;
	}
	
	int cnt = connect(cli_sock, (struct sockaddr *)&ser, sizeof(ser));
	
	if(cnt == -1) {
		perror("Error while generating connection");
		return 0;
	}
	
	connection(cli_sock);
	close(cli_sock);
}
