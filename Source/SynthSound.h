#pragma once
#include <JuceHeader.h>


class SynthSound : public juce::SynthesiserSound
{
public:
	bool appliesToNote(int)
	{
		return true;
	}
	bool appliesToChannel(int)
	{
		return true;
	}
};