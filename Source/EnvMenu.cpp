/*
  ==============================================================================

    EnvMenu.cpp
    Created: 9 Dec 2020 3:07:47pm
    Author:  kosty

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EnvMenu.h"

//==============================================================================
EnvMenu::EnvMenu(BaSynthAudioProcessor& p) : audioProcessor(p)
{

    setSize(200, 200);

    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 5000.0f);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 0.0, 0.0);
    attackSlider.setValue(0.5f);
    addAndMakeVisible(&attackSlider);

    relaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    relaseSlider.setRange(0.1f, 5000.0f);
    relaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 0.0, 0.0);
    relaseSlider.setValue(0.5f);
    addAndMakeVisible(&relaseSlider);

    decaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(1.0f, 5000.0f);
    decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 0.0, 0.0);
    decaySlider.setValue(100.0f);
    addAndMakeVisible(&decaySlider);

    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.0f, 1.0f);
    sustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 0.0, 0.0);
    sustainSlider.setValue(0.8f);
    addAndMakeVisible(&sustainSlider);

    attackTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "attack", attackSlider);
    relaseTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "relase", relaseSlider);
    decayTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "decay", decaySlider);
    sustainTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "sustain", sustainSlider);
}

EnvMenu::~EnvMenu()
{
}

void EnvMenu::paint (juce::Graphics& g)
{
    double ix = 18;

    g.drawText("Envelope", ix+5, 10, 200, 20, juce::Justification::centredLeft);

    
    g.drawText("A", ix, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("D", ix+48, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("S", ix+96, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("R", ix+144, 150, 20, 20, juce::Justification::centredTop);
   
}

void EnvMenu::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    double ix = 18;

    attackSlider.setBounds(ix-10, 38, 40, 100);
    decaySlider.setBounds(ix+38, 38, 40, 100);
    sustainSlider.setBounds(ix+86, 38, 40, 100);
    relaseSlider.setBounds(ix+134, 38, 40, 100);
}

