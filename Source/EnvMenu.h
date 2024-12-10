/*
  ==============================================================================

    EnvMenu.h
    Created: 9 Dec 2020 3:07:47pm
    Author:  kosty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class EnvMenu  : public juce::Component
{
public:
    EnvMenu(BaSynthAudioProcessor&);
    ~EnvMenu() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    

private:


    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> attackTree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> relaseTree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> decayTree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> sustainTree;

    juce::Slider attackSlider;
    juce::Slider relaseSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;

    BaSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvMenu)
};
