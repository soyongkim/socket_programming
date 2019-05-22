#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MAXBUF 1024
int main(int argc, char **argv)
{
	int server_sockfd, client_sockfd;
	int client_len, n, readn;
	char buf[MAXBUF];
	struct sockaddr_un clientaddr, serveraddr;

	if(access(argv[1], F_OK) == 0)
	{
		unlink(argv[1]);
	}


	if((server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
	{
		perror("socket error :");
		exit(0);
	}
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sun_family = AF_UNIX;
	strncpy(serveraddr.sun_path, argv[1], strlen(argv[1]));

	bind(server_sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	listen(server_sockfd, 5);

	while(1)
	{
	
		memset((void *)&clientaddr, 0x00, sizeof(clientaddr));
		printf("accept wait\n");
		client_sockfd = accept(server_sockfd, (struct sockaddr *)&clientaddr, &sizeof(clientaddr));
		while(1)
		{
			if(client_sockfd == -1)
			{
				printf("Accept Error ");
				return 0;
			}
			memset(buf, 0x00, MAXBUF);
			readn = read(client_sockfd, buf, MAXBUF);
			if(readn == 0) break;
			printf("==> %s", buf);
			write(client_sockfd, buf, strlen(buf));
		}
	}
	return 0;
} 
