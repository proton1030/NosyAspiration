/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>

//==============================================================================
NosyAspirationAudioProcessor::NosyAspirationAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    
}

NosyAspirationAudioProcessor::~NosyAspirationAudioProcessor()
{
    delete m_CGlottis;
}

//==============================================================================
const String NosyAspirationAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NosyAspirationAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NosyAspirationAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NosyAspirationAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NosyAspirationAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NosyAspirationAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NosyAspirationAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NosyAspirationAudioProcessor::setCurrentProgram (int index)
{
}

const String NosyAspirationAudioProcessor::getProgramName (int index)
{
    return {};
}

void NosyAspirationAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void NosyAspirationAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    m_CGlottis = new Glottis(sampleRate, 2);
    m_CTract = new Tract(sampleRate, 2, samplesPerBlock);
    m_CPitchTrak = new PitchTrack();
    m_CPitchTrak->init(samplesPerBlock, sampleRate);
}

void NosyAspirationAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    m_CPitchTrak->~PitchTrack();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NosyAspirationAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void NosyAspirationAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    auto inputBuff = buffer.getReadPointer(0);
    float f0 = m_CPitchTrak->getFundamentalFreq((float*)inputBuff);
    float* outputBuff = buffer.getWritePointer (0);
    m_CGlottis->process(outputBuff, outputBuff, buffer.getNumSamples());
    m_CTract->process(outputBuff, outputBuff, buffer.getNumSamples());
    
    std::cout << f0 << std::endl;
    for (int channel = 1; channel < totalNumInputChannels; channel++) {
        float* other_channel_data = buffer.getWritePointer(channel);
        memcpy(other_channel_data, outputBuff, sizeof(float) * buffer.getNumSamples());
    }

}

//==============================================================================
bool NosyAspirationAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NosyAspirationAudioProcessor::createEditor()
{
    return new NosyAspirationAudioProcessorEditor (*this);
}

//==============================================================================
void NosyAspirationAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NosyAspirationAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NosyAspirationAudioProcessor();
}
