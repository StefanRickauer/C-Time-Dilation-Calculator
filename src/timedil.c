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
 * Calculate time dilation (in years) percieved by observer on earth 
*/

double time_dilation_earth(double fac, double time_obs_trek)
{
	double time_obs_earth;
	time_obs_earth = time_obs_trek / pow(( 1 - pow(fac, 2)), 0.5);

	return time_obs_earth;
}

/* 
 * Calculate time dilation (in years) percieved by observer in space ship
*/

double time_dilation_trek(double fac, double time_obs_earth)
{
	double time_obs_trek;
	time_obs_trek = time_obs_earth * pow(( 1 - pow(fac, 2)), 0.5);

	return time_obs_trek;
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
