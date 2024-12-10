/*
  ==============================================================================

    AmpandFreq.h
    Created: 14 Dec 2020 4:11:40pm
    Author:  kosty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class AmpandFreq  : public juce::Component
{
public:
    AmpandFreq(BaSynthAudioProcessor&);
    ~AmpandFreq() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> amp1Tree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> amp2Tree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> detuneTree;

    juce::Slider amp1Slider;
    juce::Slider amp2Slider;
    juce::Slider detuneSlider;
    

    BaSynthAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpandFreq)
};
