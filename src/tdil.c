#include <stdio.h>
#include <getopt.h>
#include "timedil.h"

static const struct option long_options[] = 
{
	{ "kmh", 	required_argument, 0, 'k' },
	{ "percent", 	required_argument, 0, 'p' },
	{ "factor", 	required_argument, 0, 'f' },
	{ "years", 	required_argument, 0, 'y' },
	{ "distance", 	required_argument, 0, 'd' },
	{ "earth", 	no_argument, 0, 'e' },
	{ "trek", 	no_argument, 0, 't' },
	{ "help", 	no_argument, 0, 'h' }
};

int main(int argc, char **argv) 
{
	/*
	if(argc < 3)
	{
		fprintf(stderr, "Usage:\n\t./tdil [ -k | -p | -f ] <velocity> -y <time elapsed> [ -e | -t ]\n"
				"\t./tdil -d <distance travelled in light years> [ -k | -p | -f ] <velocity>\n");
		return 1;
	}
	*/
	int c;
	int digit_optind = 0;	
	
	while(1) 
	{
		int this_option_optind = optind ? optind : 1;
		int option_index = 0;

		c = getopt_long(argc, argv, "k:p:f:d:y:eth", long_options, &option_index);
		
		if(c == -1)
			break;

		switch(c) 
		{
			case 'k':
				printf("[TEST] option k with argument: %s\n", optarg);
				break;
			case 'p':
				printf("[TEST] option p with argument: %s\n", optarg);
				break;
			case 'f':
				printf("[TEST] option f with argument: %s\n", optarg);
				break;
			case 'y':
				printf("[TEST] option y with argument: %s\n", optarg);	
				break;
			case 'd':
				printf("[TEST] option d with argument: %s\n", optarg);
				break;
			case 'e':
				printf("[TEST] option e\n");
				break;
			case 't':
				printf("[TEST] option t\n");
				break;
			case 'h':
				printf("[TEST] option h\n");
				break;
			case '?':
				if(optopt == 'k')	printf("-k: missing argument\n");
				if(optopt == 'p')	printf("-p: missing argument\n");
				if(optopt == 'f')	printf("-f: missing argument\n");
				if(optopt == 'y')	printf("-y: missing argument\n");
				if(optopt == 'd')	printf("-d: missing argumetn\n");
				break;
		}
	}
	//double t=32.0, t_zero=10.0, v_in_kmh=1025290206.36, v_in_pct=95.0, v_in_fac=0.95, distance=4;

	

	return 0;
}
