#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "Oscillators.h"
#include "Filters.h"
#include "Modulators.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
	/*SynthVoice()
	{
		fltr = new Filter;
	}*/

	/*~SynthVoice()
	{
		delete fltr;
	}*/


	bool canPlaySound(juce::SynthesiserSound* sound) override
	{
		return dynamic_cast<SynthSound*>(sound) != nullptr;
	}

	void getParam(float* attack, float* decay, float* sustain, float* release)
	{
		env1.setAttack(double(*attack)); //20
		env1.setDecay(double(*decay)); //1000
		env1.setSustain(double(*sustain)); //1
		env1.setRelease(double(*release)); //10
	}

	void getOscType(float* selection, float* selection2)
	{
		theWave = *selection;
		theWave2 = *selection2;
	}

	double setOscType()
	{
		switch (theWave)
		{
		case 0: return osc1.sine(setDetuneLFO());
		case 1: return osc1.saw(setDetuneLFO());
		case 2: return osc1.square(setDetuneLFO());
		case 3: return osc1.triangle(setDetuneLFO());
		default: return osc1.sine(setDetuneLFO());
		}
	}

	double setOscType2()
	{
		
		switch (theWave2)
		{
		case 0: return osc2.sine(setDetune());
		case 1: return osc2.saw(setDetune());
		case 2: return osc2.square(setDetune());
		case 3: return osc2.triangle(setDetune());
		default: return osc2.sine(setDetune());
		}
	}


	void setFilter(float* cutoff, float* q, float* env, float* lfo)
	{
		filterfreq = double(*cutoff);
		filterres = double(*q);
		if (env > 0)
			enva = double(*env) * (4.3 - filterfreq);
		else
			enva = double(*env) * (filterfreq - 1);


		if (lfo > 0)
			filterLfo = double(*lfo) * (4.3 - filterfreq - env1.adsr(enva));
		else
			filterLfo = double(*lfo) * (filterfreq + env1.adsr(enva) - 1);
		envb = double(*env);
		
	}

	void getAmpandFreq(float* amp11, float* amp22, float* detune1)
	{
		amp1 = double(*amp11);
		amp2 = double(*amp22);
		detune = double(*detune1);
	}

	double setDetune()
	{
		return frequency + (0.059463094*frequency) * detune + (0.059463094 * frequency) * freqMod * lfo1.sine(BPM, freqSet); // 2^(1/12)-1 :: 1 semitone detune
	}

	double setDetuneLFO()
	{
		return frequency + (0.059463094 * frequency) * freqMod*lfo1.sine(BPM, freqSet); // 2^(1/12)-1 :: 1 semitone detune
	}

	void getLFO(float* freqsett, float* ampmodd, float* freqmodd, double bpm)
	{
		freqSet= double(*freqsett);
		ampMod= double(*ampmodd);
		freqMod= double(*freqmodd);
		BPM=bpm;
		
	}

	void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override
	{
		env1.trigger = 1;
		//env1.setTrigger(1);
		frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
		level = velocity;
		if (fltr==nullptr)
			fltr = new Filter;
		//fltr->reset();
		lfo1.resetPhase();

	}
	void stopNote(float velocity, bool allowTailOff) override
	{
		env1.trigger = 0;
		//env1.setTrigger(0);

		allowTailOff = true;
		if (velocity == 0)
				clearCurrentNote();
	}

	void renderNextBlock( juce::AudioBuffer <float> & outputBuffer, int startSample, int numSamples) override
	{
	
		
		for (int sample = 0; sample < numSamples; sample++)
		{
			if (envb > 0.0 && filterfreq > 4.3)
				fltr->setFreqAndQ(juce::Decibels::decibelsToGain((filterfreq) * 20), filterres);
			else
				fltr->setFreqAndQ(juce::Decibels::decibelsToGain((filterfreq + env1.adsr(enva) + filterLfo * lfo1.sine(BPM, freqSet)) * 20), filterres);
			//double theWave = osc1.saw(frequency);
			double theSound = fltr->process((amp1 * setOscType() + amp2 * setOscType2()) / 2);
			theSound = env1.adsr(theSound) * level;
			theSound = (1+ampMod*lfo1.sine(BPM, freqSet))*theSound/2;
			

			for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
			{
				outputBuffer.addSample(channel, startSample, theSound);
			}

			startSample++;
		}


	}

	void pitchWheelMoved(int newPitchWheelValue) override
	{

	}
	void controllerMoved(int controllerNumber, int newControllerValue) override
	{

	}


private:
	double level;
	double frequency;
	int theWave, theWave2;
	Osc osc1;
	Osc osc2;
	
	Filter* fltr;
	Mod env1;
	Mod lfo1;

	double filterfreq, filterres, enva, envb, filterLfo;
	double amp1, amp2, detune;
	double freqSet, ampMod, freqMod, BPM;

};

