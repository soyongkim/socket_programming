#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define MAXLINE 1024

int main(int argc, char **argv)
{
	struct sockaddr_un serveraddr;
	int server_sockfd;
	int server_len;
	char buf[MAXLINE];

	if(access(argv[1], R_OK) == -1)
	{
		printf("socket File access error\n");
		return 1;
	}

	if((server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
	{
		perror("error :");
		return 1;
	}
	memset((void *)&serveraddr, 0x00, sizeof(serveraddr));
	serveraddr.sun_family = AF_UNIX;
	strncpy(serveraddr.sun_path, argv[1], strlen(argv[1]));
	server_len = sizeof(serveraddr);
	if((connect(server_sockfd, (struct sockaddr *)&serveraddr, server_len)) == -1)
	{
		perror("connect error :");
		return 1;
	}
	while(1)
	{
		memset(buf, 0x00, MAXLINE);
		read(0, buf, MAXLINE);
		if(strncmp(buf, "quit\n", 5) == 0)
		{
			break;
		}
		write(server_sockfd, buf, strlen(buf));
		read(server_sockfd, buf, MAXLINE);
		printf("Server : %s", buf);
	}
	return 0;
}

