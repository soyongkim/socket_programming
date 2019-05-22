#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/time.h>

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
	struct sockaddr_in client_addr, server_addr;
	int listen_sockfd, client_sockfd;
	int addr_len;
	struct cal_data rdata;
	int lnum, rnum;
	int cal_res;

	if((listen_sockfd=socket(AF_INET, SOCK_STREAM,0)) == -1 ) {
		perror("socket error ");
		return 1;
	}
	
	memset((void *)&server_addr, 0x00, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(atoi(argv[1]));

	if(bind(listen_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1 )
	{
		perror("Bind error ");
		return 1;
	}

	if(listen(listen_sockfd, 5) == -1)
	{
		perror("Listen error ");
		return 1;
	}

	while(1) {
		addr_len = sizeof(client_addr);
		memset((void *)&client_addr, 0x00, addr_len);
		if((client_sockfd = accept(listen_sockfd,(struct sockaddr *)&client_addr,&addr_len)) == -1)
		{
			perror("Acceptance error ");
			return 1;
		} 
		printf("New client connect %s \n", inet_ntoa(client_addr.sin_addr));

		read(client_sockfd, (void *)&rdata, sizeof(rdata));
		rdata.error = 0;
		
		lnum = ntohl(rdata.left_num);
		rnum = ntohl(rdata.right_num);

		switch(rdata.op)
		{
			case '+':
				cal_res = lnum+rnum;
				break;
			case '-':
				cal_res = lnum-rnum;
				break;
			case 'x':
				cal_res = lnum*rnum;
				break;
			case '/':
				if(rnum==0) { rdata.error=2; break;}
				cal_res = lnum/rnum;
				break;
			default:
				rdata.error=1;
		}
			
		rdata.result = htonl(cal_res);
		rdata.error = htons(rdata.error);

		write(client_sockfd, (void *)&rdata, sizeof(rdata));

		close(client_sockfd);
	}

	close(listen_sockfd);
	return 0;
}
