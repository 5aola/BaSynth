/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "OscMenu.h"
#include "EnvMenu.h"
#include "FilterMenu.h"
#include "AmpandFreq.h"
#include "LfoMenu.h"

//==============================================================================
/**
*/
class BaSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
                                    
{
public:
    BaSynthAudioProcessorEditor (BaSynthAudioProcessor&);
    ~BaSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

   

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    BaSynthAudioProcessor& audioProcessor;

    OscMenu oscGUI;

    EnvMenu envGUI;

    FilterMenu filterGUI;

    AmpandFreq ampGUI;

    LfoMenu lfoGUI;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BaSynthAudioProcessorEditor)
};
