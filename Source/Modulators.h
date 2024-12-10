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

class Mod {
private:

	double frequency;
	double phase;
	double output;

	double sampleRate;

	double input;
	double attack;
	double decay;
	double sustain;
	double release;
	double amplitude;


	

	int attackphase, decayphase, sustainphase, releasephase;


public:

	int trigger;

	Mod() {
		sampleRate = 44100.0;
		phase = 0.0;
		output = 0.0;

		input = 0;
		attack = 0;
		decay = 0;
		sustain = 0;
		release = 0;
		amplitude = 0;

		trigger=0;

		attackphase = 0;
		decayphase = 0;
		sustainphase = 0;
		releasephase = 0;
	}

	void resetPhase()
	{
		phase = 0;
	}
	double sine(double BPM, double rate)
	{
		output = sin(phase * (TWOPI));
		if (phase >= 1.0) phase -= 1.0;
		phase += (1. / (sampleRate / (rate * BPM / 480)));
		return(output);
	}


	// ------------------------------------------------
	
	
	int getTrigger() const {
		return trigger;
	}


	void setTrigger(int trigger) {
		this->trigger = trigger;
	}

	double adsr(double input)
	{
		if (trigger == 1)
		{
			if (attackphase != 1 && sustainphase != 1 && decayphase != 1) {
				decayphase = 0;
				sustainphase = 0;
				releasephase = 0;
				attackphase = 1;
			}
			if (attackphase == 1) {
				releasephase = 0;
				amplitude += attack;
				output = input * amplitude;

				if (amplitude >= 1) {
					amplitude = 1;
					attackphase = 0;
					decayphase = 1;
				}
			}
			if (decayphase == 1) {
				amplitude -= decay;
				output = input * (amplitude);
				if (amplitude <= sustain) {
					decayphase = 0;
					sustainphase = 1;
				}
			}
			if (sustainphase == 1) {
				output = input * amplitude;
			}
		}
		else
		{
			output = input * (amplitude *= release);
			decayphase = 0;
			sustainphase = 0;
			releasephase = 0;
			attackphase = 1;
		}
		return output;
	}

	void setAttack(double attackMS) {
		attack = 1 - pow(0.01, 1.0 / (attackMS * sampleRate * 0.001));
	}

	void setRelease(double releaseMS) {
		release = pow(0.01, 1.0 / (releaseMS * sampleRate * 0.001));
	}

	void setSustain(double sustainL) {
		sustain = sustainL;
	}

	void setDecay(double decayMS) {
		decay = 1-pow(0.01, 1.0 / (decayMS * sampleRate * 0.001));
	}

};
