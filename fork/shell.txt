#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_LINE 256
#define PROMPT "# "
#define chop(str) str[strlen(str)-1] = 0x00;


int main(int argc, char **argv)
{
	char buf[MAX_LINE];
	int proc_status;
	pid_t pid;
	printf("My Shell Ver 2.0\n");
	signal(SIGCHLD, SIG_IGN);
	while(1) {
		printf("%s", PROMPT);
		memset(buf, 0x00, MAX_LINE);
		fgets(buf, MAX_LINE-1, stdin);
		if(strncmp(buf, "quit\n", 5) == 0)
		{
			break;
		}
		chop(buf);
		pid = fork();
		if(pid == 0)
		{
		printf("Parents PID: %d\n", getppid());
		printf("Child   PID: %d\n", getpid()); 
		if(execl(buf, buf, NULL) == -1)
			{
				printf("Execl failure\n");
				exit(0);
			}
		}
		if(pid > 0)
		{
			printf("Child wait\n");
			wait(&proc_status);
			//waitpid(1,&proc_status,WNOHANG);
			printf("Child exit\n");
		}
	}
	return 0;
}
