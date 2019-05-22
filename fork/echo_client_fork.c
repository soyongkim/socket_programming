#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 1024

int main(int argc, char **argv)
{
	struct sockaddr_in serveraddr;
	int server_sockfd;
	int client_len;
	char buf[MAXLINE];
	int connect_chk;
	int sockfd_chk;	
	if(sockfd_chk = (server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("error :");
		return 1;
	}
	printf("Sokect make: %d\n", sockfd_chk);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(3600);
	
	client_len = sizeof(serveraddr);
	if((connect_chk = connect(server_sockfd, (struct sockaddr *)&serveraddr, client_len)) == -1)
	{
		perror("connect error :");
		return 1;
	}
	printf("Connect success: %d\n", connect_chk);
	while(1) {
	memset(buf, 0x00, MAXLINE);
	read(0, buf, MAXLINE);
	if(write(server_sockfd, buf, MAXLINE) <= 0)
	{
		perror("write error :");
		return 1;
	}
	printf("me: %s\n", buf);
	memset(buf, 0x00, MAXLINE);
	if(read(server_sockfd, buf, MAXLINE) <= 0)
	{
		perror("read error :");
		return 1;
	}
	printf("server: %s\n", buf);
	}
	close(server_sockfd);;
	return 0;
}
