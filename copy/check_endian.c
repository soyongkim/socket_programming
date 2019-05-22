#include <stdio.h>

int check_endian(void);
int main(int argc, char **argv)
{
	int endian;
	endian = check_endian();
	if(endian == 1) printf("This system is Little endian\n");
	else printf("This system is Big endian\n");
	return 0;
}

int check_endian(void)
{
	int a=1;
	return ((char*)&a)[0]? 1: 0;
}
