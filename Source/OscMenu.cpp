/*
  ==============================================================================

    OscMenu.cpp
    Created: 9 Dec 2020 1:48:12pm
    Author:  kosty

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscMenu.h"

//==============================================================================
OscMenu::OscMenu(BaSynthAudioProcessor& p) : audioProcessor(p)
{
    setSize(150, 200);

    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Saw", 2);
    oscMenu.addItem("Square", 3);
    oscMenu.addItem("Triangle", 4);
    oscMenu.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(&oscMenu);
    oscMenu.addListener(this);

    oscMenu2.addItem("Sine", 1);
    oscMenu2.addItem("Saw", 2);
    oscMenu2.addItem("Square", 3);
    oscMenu2.addItem("Triangle", 4);
    oscMenu2.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(&oscMenu2);
    oscMenu2.addListener(this);

    waveSelection = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.tree, "wavetype", oscMenu);
    waveSelection2 = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.tree, "wavetype2", oscMenu2);

}

OscMenu::~OscMenu()
{
}

void OscMenu::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Oscillators", 23, 10, 200, 20, juce::Justification::centredLeft);
}

void OscMenu::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    oscMenu.setBounds(area.removeFromTop(20));
    oscMenu2.setBounds(area.removeFromBottom(20));
}

void OscMenu::comboBoxChanged(juce::ComboBox* box)
{

}
