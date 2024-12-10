/*
  ==============================================================================

    AmpandFreq.cpp
    Created: 14 Dec 2020 4:11:40pm
    Author:  kosty

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AmpandFreq.h"

//==============================================================================
AmpandFreq::AmpandFreq(BaSynthAudioProcessor& p) : audioProcessor(p)
{
    setSize(150, 200);

    amp1Slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    amp1Slider.setRange(0.0f, 1.0f);
    amp1Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 0.0, 0.0);
    amp1Slider.setValue(1.0f);
    addAndMakeVisible(&amp1Slider);

    amp2Slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    amp2Slider.setRange(0.0f, 1.0f);
    amp2Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 0.0, 0.0);
    amp2Slider.setValue(0.0f);
    addAndMakeVisible(&amp2Slider);

    detuneSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    detuneSlider.setRange(0.0f, 1.0f);
    detuneSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 0.0, 0.0);
    detuneSlider.setValue(0.0f);
    addAndMakeVisible(&detuneSlider);

    amp1Tree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "amp1", amp1Slider);
    amp2Tree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "amp2", amp2Slider);
    detuneTree = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "detune", detuneSlider);

}

AmpandFreq::~AmpandFreq()
{
}

void AmpandFreq::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);

    g.drawText("Level", 0, 10, 50, 20, juce::Justification::centred);
    g.drawText("Detune", 50, 10, 50, 20, juce::Justification::centred);

}

void AmpandFreq::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    double ix = 5;

    amp1Slider.setBounds(ix, 30, 40, 80);
    amp2Slider.setBounds(ix, 100, 40, 80);
    detuneSlider.setBounds(ix + 50, 100, 40, 80);
}
