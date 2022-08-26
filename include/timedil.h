#ifndef TIME_DIL_H
#define TIME_DIL_H

/*
 * 	Speed of Light (c) 	=       299 792 458 m/s 
 * <=>	Speed of Light / 1000 	=       299 792,458 km/s
 * <=>	Speed of Light * 3600	= 1 079 252 848,800 km/h
*/

#define C 1079252848.8l

double kmh_to_pct(double );
double pct_to_fac(double );
double fac_to_kmh(double );
double time_dilation_earth(double , double );
double time_dilation_trek(double , double );
double travel_duration_earth(double, double);

#endif
