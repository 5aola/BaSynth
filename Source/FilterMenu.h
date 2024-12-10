/*
  ==============================================================================

    FilterMenu.h
    Created: 9 Dec 2020 4:32:27pm
    Author:  kosty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class FilterMenu  : public juce::Component
{
public:
    FilterMenu(BaSynthAudioProcessor&);
    ~FilterMenu() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    BaSynthAudioProcessor& audioProcessor;

    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> cutoffTree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> resTree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> envAmountTree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> lfoAmountTree;

    juce::Slider cutoffFreq;
    juce::Slider resSlider;
    juce::Slider envAmount;
    juce::Slider lfoAmount;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterMenu)
};
