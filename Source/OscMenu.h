/*
  ==============================================================================

    OscMenu.h
    Created: 9 Dec 2020 1:48:12pm
    Author:  kosty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class OscMenu  : public juce::Component, private juce::ComboBox::Listener
{
public:
    OscMenu(BaSynthAudioProcessor&);
    ~OscMenu() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void comboBoxChanged(juce::ComboBox*) override;

private:

    BaSynthAudioProcessor& audioProcessor;

    juce::ComboBox oscMenu;
    juce::ComboBox oscMenu2;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscMenu)
};
