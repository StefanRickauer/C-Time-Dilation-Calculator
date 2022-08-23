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
	
	if(argc < 3)
	{
		fprintf(stderr, "%s", help_text);
				
		return 1;
	}
	
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
