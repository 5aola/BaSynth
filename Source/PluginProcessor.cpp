/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BaSynthAudioProcessor::BaSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), 
    //lowPassFilter(juce::dsp::IIR::Coefficients<float>::makeLowPass(44100, 2000.0f, 0.1f)),
    
    tree (*this,nullptr)
#endif
{
    juce::NormalisableRange<float> attackParam (0.1f, 5000.0f);
    juce::NormalisableRange<float> relaseParam(0.1f, 5000.0f);
    juce::NormalisableRange<float> decayParam(1.0f, 5000.0f);
    juce::NormalisableRange<float> sustainParam(0.0f, 1.0f);

    tree.createAndAddParameter("attack", "Attack", "attack", attackParam, 20.0f, nullptr, nullptr);
    tree.createAndAddParameter("relase", "Relase", "relase", relaseParam, 30.0f, nullptr, nullptr);
    tree.createAndAddParameter("decay", "Decay", "decay", decayParam, 100.0f, nullptr, nullptr);
    tree.createAndAddParameter("sustain", "Sustain", "sustain", sustainParam, 1.0f, nullptr, nullptr);

    juce::NormalisableRange<float> cutoffParam(1.0f, 4.3f);
    juce::NormalisableRange<float> resParam(0.0f, 1.0f);
    juce::NormalisableRange<float> envamountParam(-1.0f, 1.0f);
    juce::NormalisableRange<float> lfoamountParam(-1.0f, 1.0f);

    tree.createAndAddParameter("cutoff", "Cutoff", "cutoff", cutoffParam, 4.3f, nullptr, nullptr);
    tree.createAndAddParameter("res", "Res", "res", resParam, 0.0f, nullptr, nullptr);
    tree.createAndAddParameter("envamount", "Envamount", "envamount", envamountParam, 0.0f, nullptr, nullptr);
    tree.createAndAddParameter("lfoamount", "Lfoamount", "lfoamount", lfoamountParam, 0.0f, nullptr, nullptr);



    juce::NormalisableRange<float> wavetypeParam(0, 3);
    tree.createAndAddParameter("wavetype", "WaveType", "wavetype", wavetypeParam, 1, nullptr, nullptr);
    juce::NormalisableRange<float> wavetype2Param(0, 3);
    tree.createAndAddParameter("wavetype2", "WaveType2", "wavetype2", wavetype2Param, 1, nullptr, nullptr);

    juce::NormalisableRange<float> amp1Param(0.0f, 1.0f);
    juce::NormalisableRange<float> amp2Param(0.0f, 1.0f);
    juce::NormalisableRange<float> detuneParam(0.0f, 1.0f);

    tree.createAndAddParameter("amp1", "Amp1", "amp1", amp1Param, 1.0f, nullptr, nullptr);
    tree.createAndAddParameter("amp2", "Amp2", "amp2", amp2Param, 0.0f, nullptr, nullptr);
    tree.createAndAddParameter("detune", "Detune", "detune", detuneParam, 0.0f, nullptr, nullptr);

    juce::NormalisableRange<float> freqsetParam(1.0f, 16.0f);
    juce::NormalisableRange<float> ampmodParam(-1.0f, 1.0f);
    juce::NormalisableRange<float> freqmodParam(-1.0f, 1.0f);

    tree.createAndAddParameter("freqset", "Freqset", "freqset", freqsetParam, 1.0f, nullptr, nullptr);
    tree.createAndAddParameter("ampmod", "Ampmod", "ampmod", ampmodParam, 0.0f, nullptr, nullptr);
    tree.createAndAddParameter("freqmod", "Freqmod", "freqmod", freqmodParam, 0.0f, nullptr, nullptr);

    mySynth.clearVoices();

    for (int i = 0; i < 5; i++)
    {
        mySynth.addVoice(new SynthVoice());
    }
    

    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
    
}

BaSynthAudioProcessor::~BaSynthAudioProcessor()
{
}

//==============================================================================
const juce::String BaSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BaSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BaSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BaSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BaSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BaSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BaSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BaSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BaSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void BaSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BaSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();


   // lowPassFilter.prepare(spec);
    //lowPassFilter.reset();
}

void BaSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BaSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BaSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{

    playHead = this->getPlayHead();
    playHead->getCurrentPosition(currentPositionInfo);
    double bpm = currentPositionInfo.bpm; //get the tempo from the DAW

    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
        {
            float* newFloatPtra = (float*)tree.getRawParameterValue("attack");
            float* newFloatPtrr = (float*)tree.getRawParameterValue("relase");
            float* newFloatPtrd = (float*)tree.getRawParameterValue("decay");
            float* newFloatPtrs = (float*)tree.getRawParameterValue("sustain");
            myVoice->getParam(newFloatPtra, newFloatPtrd, newFloatPtrs, newFloatPtrr);
            
            float* newFloatPtrw = (float*)tree.getRawParameterValue("wavetype");
            float* newFloatPtrw2 = (float*)tree.getRawParameterValue("wavetype2");
            myVoice->getOscType(newFloatPtrw, newFloatPtrw2);

            float* newFloatPtrc = (float*)tree.getRawParameterValue("cutoff");
            float* newFloatPtrq = (float*)tree.getRawParameterValue("res");
            float* newFloatPtrenva = (float*)tree.getRawParameterValue("envamount");
            float* newFloatPtrlfoa = (float*)tree.getRawParameterValue("lfoamount");
            myVoice->setFilter(newFloatPtrc, newFloatPtrq, newFloatPtrenva, newFloatPtrlfoa);

            float* newFloatPtra1 = (float*)tree.getRawParameterValue("amp1");
            float* newFloatPtra2 = (float*)tree.getRawParameterValue("amp2");
            float* newFloatPtrdt = (float*)tree.getRawParameterValue("detune");
            myVoice->getAmpandFreq(newFloatPtra1, newFloatPtra2, newFloatPtrdt);

            float* newFloatPtrfs = (float*)tree.getRawParameterValue("freqset");
            float* newFloatPtram = (float*)tree.getRawParameterValue("ampmod");
            float* newFloatPtrfm = (float*)tree.getRawParameterValue("freqmod");
            myVoice->getLFO(newFloatPtrfs, newFloatPtram, newFloatPtrfm, bpm);
           
        }
    }

    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());


    /*
    juce::dsp::AudioBlock <float> block(buffer);
    *lowPassFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(lastSampleRate, 2000.0f, 1.0f);
    lowPassFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
    */

}

//==============================================================================
bool BaSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BaSynthAudioProcessor::createEditor()
{
    return new BaSynthAudioProcessorEditor (*this);
}

//==============================================================================
void BaSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BaSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BaSynthAudioProcessor();
}
