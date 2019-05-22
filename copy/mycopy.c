#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#define MAXLINE 512
int main(int argc, char **argv)
{
	int source_fd;
	int dest_fd;
	int readn;
	int totaln=0;
	char buf[MAXLINE];

	if(argc != 3)
	{
		fprintf(stderr, "Usage : %s [source file] [dest file]\n", argv[0]);
		return 1;
	}
	if((source_fd = open(argv[1], O_RDONLY)) == -1 )
	{
		perror("Error :");
		return 1;
	}
 	if((dest_fd = open(argv[2], O_CREAT|O_EXCL|O_WRONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == -1 )
	{
		perror("Error dest_fd :");
		return 1;
	}
	if(errno == EEXIST)
	{
		perror("Error eexist :");
		close(dest_fd);
		return 1;
	}
	
	memset(buf, 0x00, MAXLINE);
	while((readn = read(source_fd, buf, MAXLINE)) > 0 )
	{
		printf("readn : %d\n", readn);
		totaln+=write(dest_fd, buf, readn);
		memset(buf, 0x00, MAXLINE);		
	}
	printf("Total Copy Size : %d\n", totaln);
	return 0;
}
