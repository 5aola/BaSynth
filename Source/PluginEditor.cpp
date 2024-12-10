/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BaSynthAudioProcessorEditor::BaSynthAudioProcessorEditor (BaSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), oscGUI(p), envGUI(p), filterGUI(p), ampGUI(p), lfoGUI(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (900, 200);

    addAndMakeVisible(&oscGUI);
    addAndMakeVisible(&ampGUI);
    addAndMakeVisible(&envGUI);
    addAndMakeVisible(&filterGUI);
    addAndMakeVisible(&lfoGUI);
   

}

BaSynthAudioProcessorEditor::~BaSynthAudioProcessorEditor()
{
}

//==============================================================================
void BaSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void BaSynthAudioProcessorEditor::resized()
{
    juce::Rectangle<int> area = getLocalBounds();

    const int componentWidth = 200;
    const int componentHeight = 200;

    oscGUI.setBounds(area.removeFromLeft(180).removeFromTop(componentHeight));
    ampGUI.setBounds(area.removeFromLeft(120).removeFromTop(componentHeight));
    envGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    filterGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    lfoGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));

    
}

