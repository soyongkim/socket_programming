#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	printf("----START %d----\n",getpid());
	execl("/bin/ls","ls", NULL);
	//execl("./exec_text", "exec_text", NULL);
	printf("-----END-----\n");
	return 0;	
}
