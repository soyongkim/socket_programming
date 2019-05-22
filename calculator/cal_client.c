#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>

struct cal_data
{
	int left_num;
	int right_num;
	char op;
	int result;
	short int error;
};

int main(int argc, char **argv)
{
	struct sockaddr_in sockaddr;
	int sockfd;
	int sdata_len;
	int sbyte, rbyte;
	struct cal_data sdata;

	if(argc != 4)
	{
		printf("Usage: %s [num1][op][num2]\n", argv[0]);
		return 1;
	}
	
	memset((void *)&sdata, 0x00, sizeof(sdata));
	//sdata.left_num = atoi(argv[1]);
	//sdata.right_num = atoi(argv[3]);
	sdata.op = argv[2][0];
	
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket error :");
		return 1;
	}

	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockaddr.sin_port = htons(3600);

	/* server connect */
	if(connect(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) == -1)
	{
		perror("connect error ");
		return 1;
	}

	sdata_len = sizeof(sdata);
	sdata.left_num = htonl(atoi(argv[1]));
	sdata.right_num = htonl(atoi(argv[3]));
	
	sbyte = send(sockfd, (char *)&sdata, sdata_len, 0);
	if(sbyte != sdata_len)
	{
		printf("Error in sending messages\n");
		return 1;
	}

	rbyte = recv(sockfd, (char *)&sdata, sdata_len, 0);
	if(rbyte != sdata_len)
	{
		printf("Error in receving messages\n");
		return 1;
	}

	if(ntohs(sdata.error) != 0 )
		printf("Caculation error %d \n", ntohs(sdata.error));
	printf("%d %c %d = %d \n", ntohl(sdata.left_num), sdata.op, ntohl(sdata.right_num), ntohl(sdata.result));

	close(sockfd);
	return 0;
}
