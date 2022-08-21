#include <math.h>
#include "timedil.h"

// Convert velocity into percent of speed of light

double kmh_to_pct(double velocity)
{
	double pct;
	pct = (velocity * 100) / C;

	return pct;
}

// Convert percent of lightspeed into factor to be multiplied with c (speed of light)

double pct_to_fac(double pct)
{
	double fac;
	fac = pct / 100;

	return fac;
}

// Convert factor into kilometers per hour

double fac_to_kmh(double fac) 
{
	return C * fac;
}

/*
 * Calculate time dilation (in years) percieved by observer A
*/

double time_dilation_A(double fac, double time_obs_B)
{
	double time_obs_A;
	time_obs_A = time_obs_B / pow(( 1 - pow(fac, 2)), 0.5);

	return time_obs_A;
}

/* 
 * Calculate time dilation (in years) percieved by observer B (traveling at )
*/

double time_dilation_B(double fac, double time_obs_A)
{
	double time_obs_B;
	time_obs_B = time_obs_A * pow(( 1 - pow(fac, 2)), 0.5);

	return time_obs_B;
}

/*
 * Calcualte travel duration (as percieved by observer A) 
 * based on distance in light years and velocity (factor)
 *
*/

double travel_duration_A(double dist, double fac)
{
	return dist / fac;
}
