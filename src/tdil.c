#include <stdio.h>
#include "timedil.h"

int main(int argc, char **argv) 
{
	if(argc < 2)
	{
		fprintf(stderr, "[! TEST CASE] Run program with ./bin/tdil <any input>\n");
		return 1;
	}
	printf("Running tests\n\n");
	
	double t=10.0, t_zero=32.0, v_in_kmh=1025290206.0, v_in_pct=95.0, v_in_fac=0.95;

	double test1 = kmh_to_pct(v_in_kmh);

	int errors = 0;
	
	if(test1 - v_in_pct > 0.000001) 
	{
		fprintf(stderr, "Error in function \"kmh_to_pct\", expected %lf and got %lf\n", v_in_pct, test1);
		errors++;
	}

	printf("Errors in total: %d\n", errors);

	return 0;
}
