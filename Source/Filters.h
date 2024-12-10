/*
  ==============================================================================

    Filters.h
    Created: 24 Nov 2020 11:37:22am
    Author:  kosty

  ==============================================================================
*/

#include <cmath>
#include <algorithm>
#include <JuceHeader.h>

#ifndef PI
#define PI  3.1415926535897932384626433832795
#endif

#pragma once

class Filter
{
public:
	

	Filter() { reset(); }
	inline void setFreqAndQ(double frequency, double q);

	inline double process(double sample);
	inline double comp(double x);

	inline void reset();
protected:

	double sampleRate;
	double invSampleRate;

	double d1;
	double d2;
	double d3;
	double d4;
	double d5;
	double d6;
	double d7;
	double d8;

	double g;
	double Gres;
};

//-----------------------------------------------------------------------------
void Filter::reset()
{
	sampleRate = 44100.;
	invSampleRate = 1./44100.;

	d1 = d2 = d3 = d4 = d5 = d6 = d7 = d8 = 0.;
	Gres = 0.;
	g = 0.;
}
//-----------------------------------------------------------------------------
void Filter::setFreqAndQ(double freq, double q /* 0 < q < 1 */)
{
	//static const double M_LOG2 = log(2.0);

	double const omega = 2.0 * PI * freq * invSampleRate;
	//double const tsin = sin(omega);
	//double const tcos = cos(omega);


	Gres = q * (1.0029 + 0.0526 * omega - 0.0926 * omega * omega + 0.0218 * omega * omega * omega);

	g = 0.9892 * omega - 0.4342 * omega * omega + 0.1381 * omega * omega * omega - 0.0202 * omega * omega * omega * omega;
	
}

double Filter::comp(double x)
{
	return (atan(x));
}


//-----------------------------------------------------------------------------
double Filter::process(double sample)
{

	double output1 = comp(sample - (d8 - sample * 0.5) * Gres * 4) / 1.3 * g + d1 * (0.3 / 1.3) * g - d2 * g + d2;
	d1 = sample;
	d2 = output1;

	double output2 = output1 / 1.3 * g + d3 * (0.3 / 1.3) * g - d4 * g + d4;
	d3 = output1;
	d4 = output2;

	double output3 = output2 / 1.3 * g + d5 * (0.3 / 1.3) * g - d6 * g + d6;
	d5 = output2;
	d6 = output3;

	double output4 = output3 / 1.3 * g + d7 * (0.3 / 1.3) * g - d8 * g + d8;
	d7 = output3;
	d8 = output4;

	double output = output4;

	return  output;
}