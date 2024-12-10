/*
  ==============================================================================

    LfoMenu.cpp
    Created: 14 Dec 2020 6:04:20pm
    Author:  kosty

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LfoMenu.h"

//==============================================================================
LfoMenu::LfoMenu(BaSynthAudioProcessor& p) : audioProcessor(p)
{
    setSize(200, 200);

    freqSetSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    freqSetSlider.setRange(1.0f, 16.0f);
    freqSetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 0.0, 0.0);
    freqSetSlider.setValue(0.5f);
    addAndMakeVisible(&freqSetSlider);

    ampModSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    ampModSlider.setRange(0.1f, 5000.0f);
    ampModSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 0.0, 0.0);
    ampModSlider.setValue(0.5f);
    addAndMakeVisible(&ampModSlider);

    freqModSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    freqModSlider.setRange(1.0f, 2000.0f);
    freqModSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 0.0, 0.0);
    freqModSlider.setValue(100.0f);
    addAndMakeVisible(&freqModSlider);

    freqSetTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "freqset", freqSetSlider);
    ampModTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "ampmod", ampModSlider);
    freqModTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "freqmod", freqModSlider);
}

LfoMenu::~LfoMenu()
{
}

void LfoMenu::paint (juce::Graphics& g)
{
    g.drawText("LFO", 23, 10, 200, 20, juce::Justification::centredLeft);

    double ix = 20;

    g.drawText("Freq", ix, 150, 60, 20, juce::Justification::centredTop);
    g.drawText("AmpM", ix + 48, 150, 60, 20, juce::Justification::centredTop);
    g.drawText("TuneM", ix + 96, 150, 60, 20, juce::Justification::centredTop);
 
}

void LfoMenu::resized()
{
    double ix = 40;

    freqSetSlider.setBounds(ix - 10, 38, 40, 100);
    ampModSlider.setBounds(ix + 38, 38, 40, 100);
    freqModSlider.setBounds(ix + 86, 38, 40, 100);
}
