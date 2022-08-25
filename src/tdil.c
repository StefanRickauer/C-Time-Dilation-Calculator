#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>
#include "timedil.h"

// TEST CASES: 	./bin/tdil -k 45 -p 456.01 -f 433425.3434 -y 3033 -d 3434 -e -t
//		./bin/tdil -k 45 -p 56 -f 0.99 -y 3033 -d 3434 -e -t

double process_cmd_args(char opt, const char *arg);

static const struct option long_options[] = 
{
	{ "kmh", 	required_argument, 0, 'k' },
	{ "percent", 	required_argument, 0, 'p' },
	{ "factor", 	required_argument, 0, 'f' },
	{ "years", 	required_argument, 0, 'y' },
	{ "distance", 	required_argument, 0, 'd' },
	{ "earth", 	no_argument, 0, 'e' },
	{ "trek", 	no_argument, 0, 't' },
	{ "help", 	no_argument, 0, 'h' },
	{ 0, 0, 0, 0 }	
};

char *help_text = "Usage:\n\t./tdil [ -k | -p | -f ] <velocity> -y <time elapsed> [ -e | -t ]\n"
				"\t./tdil [ --kmh | --percent | --factor ] <velocity> --years <time elapsed> [ --earth | --trek ]\n\n"
				"\t./tdil [ -d ] <distance travelled in light years> [ -k | -p | -f ] <velocity>\n"
				"\t./tdil [ --distance ] <distance travelled in light years> [ --kmh | --percent | --factor ] <velocity>\n"
				"\n\n\t\t-k, --kmh      velocity in kilometers per hour, e.g. 100000000\n"
				"\t\t-p, --percent  velocity in percent of speed of light, e.g. 90\n"
				"\t\t-f, --factor   velocity as factor to be multiplied with speed of light, "
										"e.g. 0.9 (= 90 percent)\n"
				"\t\t-y, --years    time elapsed in years, e.g. 10\n"
				"\t\t-e, --earth    time elapsed as perceived by observer on earth      "
										"=> calculate time elapsed for travelling person\n"
				"\t\t-t, --trek     time elapsed as perceived by observer in space ship "
										"=> calculate time elapsed for person on earth\n"
				"\t\t-d, --distance distance travelled (default observer: earth)        "
										"=> calculate time elapsed for travelling person\n"
				"\t\t-h, --help     show this text\n\n\n";

int main(int argc, char **argv) 
{
	
	if(argc < 2)
	{
		fprintf(stderr, "%s", help_text);		
		exit(EXIT_FAILURE);
	}
	
	double vel=0.0, yrs=0.0, yrs_obs_A=0.0, yrs_obs_B=0.0, dist=0.0;

	int c;
	
	while(1) 
	{
		int option_index = 0;

		c = getopt_long(argc, argv, "k:p:f:d:y:eth", long_options, &option_index);
		
		if(c == -1)
			break;

		switch(c) 
		{
			case 'k':
				vel = process_cmd_args(c, optarg);
				printf("[TEST] Double: %f\n", vel);
				break;
			case 'p':
				vel = process_cmd_args(c, optarg);
				printf("[TEST] Double: %f\n", vel);
				break;
			case 'f':
				vel = process_cmd_args(c, optarg);
				printf("[TEST] Double: %f\n", vel);
				break;
			case 'y':
				yrs = process_cmd_args(c, optarg);
				printf("[TEST] Double: %f\n", yrs);	
				break;
			case 'd':
				dist = process_cmd_args(c, optarg);
				printf("[TEST] Double: %f\n", dist);
				break;
			case 'e':
				printf("[TEST] option e\n");
				break;
			case 't':
				printf("[TEST] option t\n");
				break;
			case 'h':
				printf("%s", help_text);
				exit(EXIT_SUCCESS);
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

	exit(EXIT_SUCCESS);
}

double process_cmd_args(char opt, const char *arg) 
{
	char **endptr;
	double input = strtod(arg, endptr);

	if(input == 0) 
	{
		if(errno == ERANGE) 
		{
			fprintf(stderr, "The value provided was out of range. Exiting.\n");
			exit(EXIT_FAILURE);
		}
	}

	if(opt == 'k')	
	{
		if(input <= 0 || input >= C)
		{
			fprintf(stderr, "The value of \"km/h\" must be between 0.0 and %Lf\n", C);
			exit(EXIT_FAILURE);
		}

		/*
		 *  Tried to assign the return values of pct_to_fac(kmh_to_pct(input)) and
		 *  pct_to_fac(input) to variable and return variable,
		 *  but this resulted in a seg fault + core dump and crashed the program (I don't know why).
		 *  Workaround for 'k' and 'p': Do not use variable and return value immediately!
		 */

		return pct_to_fac(kmh_to_pct(input));
		
	}

	else if(opt == 'p')
	{
		if(input >= 100 || input <= 0)
		{
			fprintf(stderr, "The value of \"percent\" must be between 0.0 and 100.0\n");
			exit(EXIT_FAILURE);
		}

		return pct_to_fac(input);
	}

	else if(opt == 'f' && (input <= 0 || input >= 1))
	{
		fprintf(stderr, "The value of \"factor\" must be between 0.0 and 1.0\n");
		exit(EXIT_FAILURE);
	}

	else if(opt == 'y' && input <= 0)
	{
		fprintf(stderr, "The value of \"years\" must be greater than 0.0\n");
		exit(EXIT_FAILURE);
	}

	else if(opt == 'd' && input <= 0)
	{
		fprintf(stderr, "The value of \"distance\" must be greater than 0.0\n");
		exit(EXIT_FAILURE);
	}

	return input;
}	
