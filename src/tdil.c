#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>
#include "timedil.h"

#define true  1
#define false 0

// TEST CASES (cmd line args): 	./bin/tdil -k 45 -p 456.01 -f 433425.3434 -y 3033 -d 3434 -e -t
//				./bin/tdil -k 45 -p 56 -f 0.99 -y 3033 -d 3434 -e -t

// TEST CASE (time dilation): all data
// 	time earth: 32
// 	time space: 10
// 	velocity:   0.95
// 				./bin/tdil -f 0.95 -y 10 -t	(calculates time earth: must be 32)
// 				./bin/tdil -f 0.95 -y 32 -e	(calculates time space: must be 10)
// 				./bin/tdil --percent 95 --years 10 --trek
// 				./bin/tdil --kmh 1025290206 --years 10 --trek
// 				./bin/tdil -d 30.5 -f 0.95

double process_cmd_args(char opt, const char *arg);
void print_result(double fac, double yrs_earth, 
		double yrs_trek, double dist, int extended); 

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
				"\t./tdil -d <distance travelled in light years> [ -k | -p | -f ] <velocity>\n"
				"\t./tdil --distance <distance travelled in light years> [ --kmh | --percent | --factor ] <velocity>\n"
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
	
	double vel=0.0, yrs=0.0, yrs_obs_earth=0.0, yrs_obs_trek=0.0, dist=0.0;
	int earth=false, trek=false;
	
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
				break;
			case 'p':
				vel = process_cmd_args(c, optarg);
				break;
			case 'f':
				vel = process_cmd_args(c, optarg);
				break;
			case 'y':
				yrs = process_cmd_args(c, optarg);	
				break;
			case 'd':
				dist = process_cmd_args(c, optarg);
				break;
			case 'e':
				earth = false;		
				trek = true;		// Calculate time for travelling person
				break;
			case 't':
				earth = true;		// Calculate time for person on earth
				trek = false;	
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
				if(optopt == 'd')	printf("-d: missing argument\n");
				break;
		}
	}

	// All cmd line args processed
	
	if(earth) 
	{
		yrs_obs_trek = yrs;
		yrs_obs_earth = time_dilation_earth(vel, yrs_obs_trek);
		print_result(vel, yrs_obs_earth, yrs_obs_trek, 0.0, false);
	}
	
	if(trek)
	{
		yrs_obs_earth = yrs;
		yrs_obs_trek = time_dilation_trek(vel, yrs_obs_earth);
		print_result(vel, yrs_obs_earth, yrs_obs_trek, 0.0, false);
	}
	
	if(dist > 0)
	{
		if(vel == 0)
		{
			fprintf(stderr, "%s", help_text);
			exit(EXIT_FAILURE);
		}

		yrs_obs_earth = travel_duration_earth(dist, vel);
		yrs_obs_trek = time_dilation_trek(vel, yrs_obs_earth);
		print_result(vel, yrs_obs_earth, yrs_obs_trek, dist, true);
	}
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

void print_result(double fac, double yrs_earth, double yrs_trek, double dist, int extended)
{
	double diff = yrs_earth - yrs_trek;

	printf("\n");

	if(extended)
		printf("\tDistance in ly:\t\t\t%.2f\n\n", dist);

	printf("\tSpeed in km/h:\t\t%.2f\n\tSpeed in pct of C:\t\t%.2f\n\n"
	       "\tTime elapsed earth (in yrs):\t%.2f\n\tTime elapsed space (in yrs):\t%.2f\n\n"
	       "\tTime difference (in yrs):\t%.2f\n\n", fac_to_kmh(fac), fac * 100, yrs_earth, yrs_trek, diff);
}
