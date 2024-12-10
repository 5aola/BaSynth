/*
  ==============================================================================

    LfoMenu.h
    Created: 14 Dec 2020 6:04:20pm
    Author:  kosty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class LfoMenu  : public juce::Component
{
public:
    LfoMenu(BaSynthAudioProcessor&);
    ~LfoMenu() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> freqSetTree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> ampModTree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> freqModTree;

    juce::Slider freqSetSlider;
    juce::Slider ampModSlider;
    juce::Slider freqModSlider;

    BaSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LfoMenu)
};
