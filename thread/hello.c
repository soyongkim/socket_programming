#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[])
{
	omp_set_num_threads(4);
	//#pragma omp parallel
	//#pragma omp for

	#pragma omp parallel for
	for(int i=0; i<8; i++)
	{
		printf("[%d-%d] Hello world\n", omp_get_thread_num(), i);
	}
	/* implicit barrier */
	//printf("Hello World\n");
	return 0;
}
