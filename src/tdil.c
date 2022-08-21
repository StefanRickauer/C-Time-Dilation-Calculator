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
	
	double t=32.0, t_zero=10.0, v_in_kmh=1025290206.36, v_in_pct=95.0, v_in_fac=0.95;

	double test1 = kmh_to_pct(v_in_kmh);

	int errors = 0;
	
	if(test1 - v_in_pct > 0.00001) 
	{
		fprintf(stderr, "Error in function \"kmh_to_pct\", expected %lf and got %lf\n", v_in_pct, test1);
		errors++;
	}

	double test2 = pct_to_fac(v_in_pct);

	if(test2 / 100 - v_in_fac > 0.00001)
	{
		fprintf(stderr, "Error in function \"pct_to_fac\", expected %lf and got %lf\n", v_in_fac, test2);
		errors++;
	}

	double test3 = fac_to_kmh(v_in_fac);
	
	if(test3 - v_in_kmh > 0.00001)
	{
		fprintf(stderr, "Error in function \"fac_to_kmh\", expected %lf and got %lf\n", v_in_kmh, test3);
		errors++;
	}

	double test4 = time_dilation_A(v_in_fac, t_zero);

	if(test4 - t > 0.05)
	{
		fprintf(stderr, "Error in function \"time_dilation_A\", expected %lf and got %lf\n", t, test4);
		errors++;
	}

	double test5 = time_dilation_B(v_in_fac, t);

	if(test5 - t_zero > 0.00001) 
	{
		fprintf(stderr, "Error in function \"time_dilation_B\", expected %lf and got %lf\n", t_zero, test5);
		errors++;
	}

	printf("Errors in total: %d\n", errors);

	return 0;
}
