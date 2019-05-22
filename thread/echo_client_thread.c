#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 1024
#define PORTNUM 3600

int main(int argc, char **argv)
{
	int server_fd;
	int readn;
	char buf[MAXLINE];
	int client_len;


	struct sockaddr_in server_addr;
	if( (server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("fuck!");
		return 1;
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(3600);
	client_len = sizeof(server_addr);

	if(connect(server_fd, (struct sockaddr *)&server_addr, client_len) == -1)
	{
		perror("fuck you");
		return 1;
	}
	while(1)
	{
		memset(buf, 0x00, MAXLINE);
		read(0, buf, MAXLINE);
		write(server_fd, buf, strlen(buf));
		printf("server>%s", buf);
	
	}
	close(server_fd);

}
