#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int num_steps = 1000000000;

int main()
{
	int i;
	double x,step,sum = 0.0;
	step = 1.0/(double)num_steps;
	omp_set_num_threads(4);
	#pragma omp parallel for	
	for(i=0; i<num_steps; i++) 
	{
		x = (i+0.5)*step;
		sum += 4.0/(1.0+x*x);
	}

	printf("PI = %.8f(sum=%.8f)\n", step*sum, sum);
	return 0;
}
