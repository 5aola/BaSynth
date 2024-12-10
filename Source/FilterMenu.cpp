/*
  ==============================================================================

    FilterMenu.cpp
    Created: 9 Dec 2020 4:32:27pm
    Author:  kosty

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterMenu.h"

//==============================================================================
FilterMenu::FilterMenu(BaSynthAudioProcessor& p) : audioProcessor(p)
{
    setSize(200, 200);

    cutoffFreq.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    cutoffFreq.setRange(1.0f, 4.3f);
    cutoffFreq.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 0, 0);
    cutoffFreq.setValue(4.3f);
    addAndMakeVisible(&cutoffFreq);

    resSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    resSlider.setRange(0.0f, 1.0f);
    resSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 0, 0);
    resSlider.setValue(0.0f);
    addAndMakeVisible(&resSlider);

    envAmount.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    envAmount.setRange(-1.0f, 1.0f);
    envAmount.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 0, 0);
    envAmount.setValue(0.0f);
    addAndMakeVisible(&envAmount);

    lfoAmount.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    lfoAmount.setRange(-1.0f, 1.0f);
    lfoAmount.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 0, 0);
    lfoAmount.setValue(0.0f);
    addAndMakeVisible(&lfoAmount);

    cutoffTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "cutoff", cutoffFreq);
    resTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "res", resSlider);
    envAmountTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "envamount", envAmount);
    lfoAmountTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "lfoamount", lfoAmount);
}

FilterMenu::~FilterMenu()
{
}

void FilterMenu::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);

    g.drawText("Filter", 23, 10, 200, 20, juce::Justification::centredLeft);
    double ix = 20;
    g.drawText("Freq", 0, 35, 200, 20, juce::Justification::centredTop);
    g.drawText("Res", ix, 90, 30, 20, juce::Justification::centredTop);
    g.drawText("Env", ix + 65, 90, 30, 20, juce::Justification::centredTop);
    g.drawText("LFO", ix + 130, 90, 30, 20, juce::Justification::centredTop);
}

void FilterMenu::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    double ix = 15;

    cutoffFreq.setBounds(25, 55, 150, 30);
    resSlider.setBounds(ix, 100, 40, 100);
    envAmount.setBounds(ix + 65, 100, 40, 100);
    lfoAmount.setBounds(ix + 130, 100, 40, 100);
}
