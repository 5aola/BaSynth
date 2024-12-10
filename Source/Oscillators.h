/*
  ==============================================================================

    Oscillators.h
    Created: 23 Nov 2020 6:22:37pm
    Author:  kosty

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

#ifndef PI
#define PI  3.1415926535897932384626433832795
#endif
#define TWOPI 6.283185307179586476925286766559

class Osc {
private:

	double frequency;
	double phase;
	double phase2;
	double bphase;
	double output;
	double z1;
	double z2;
	double rate;
	double sq;
	double out1, out2;


public:
	Osc() {
		rate = 44100.0;
		frequency = 0.0;
		phase = 0.0;
		phase2 = 0.0;
		bphase = 0.0;
		output = 0.0;
		z1 = 0.0;
		z2 = 0.0;
		sq = 0.0;
		out1 = 0.0;
		out2 = 0.0;
	};

	double sine(double frequency) 
	{
		output = sin(phase * (TWOPI));
		if (phase >= 1.0) phase -= 1.0;
		phase += (1. / (rate / (frequency)));
		return(output);
	};
	
	double saw(double frequency)
	{
		phase += (frequency / rate);
		if (phase >= 1.0) 
			phase -= 1;

		bphase = 2 * phase - 1;
		sq = bphase*bphase;
		output = sq - z1;
		z1 = sq;
		return(output * rate/(frequency*4));
	};

	double square(double frequency, double duty = 0.5 /*0 és 1 közötti érték*/ )
	{
		phase += (frequency / rate);
		if (phase >= 1.0)
			phase -= 1;
		bphase = 2 * phase - 1;
		sq = bphase * bphase;
		output = sq - z1;
		z1 = sq;
		out1 = output * rate / (frequency * 8);
		
		phase2 = phase + duty;
		if (phase2 >= 1)
			phase2 -= 1;
		bphase = 2 * phase2 - 1;
		sq = bphase * bphase;
		output = sq - z2;
		z2 = sq;
		out2 = output * rate / (frequency * 8);

		return(out1 - out2);
	};

	double triangle(double frequency)
	{
		phase += (frequency / rate);
		if (phase >= 1.0)
			phase -= 1;
		bphase = 2 * phase - 1;
		sq = bphase * bphase;
		output = sq - z1;
		z1 = sq;
		out1 = output * rate / (frequency * 8);

		phase2 = phase + 0.5;
		if (phase2 >= 1)
			phase2 -= 1;
		bphase = 2 * phase2 - 1;
		sq = bphase * bphase;
		output = sq - z1; // z1<-->z2
		z1 = sq;
		out2 = output * rate / (frequency * 8);
		
		return((out1 - out2)/20);
	};

};