/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Glottis.h"
#include "Tract.h"
#include "PitchTrack.h"
#include "OnsetDetection.h"
#include "Sequencer.h"

//==============================================================================
/**
*/
class NosyAspirationAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    NosyAspirationAudioProcessor();
    ~NosyAspirationAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    Glottis*            m_CGlottis = 0;
    Tract*              m_CTract = 0;
    PitchTrack*         m_CPitchTrak = 0;
    OnsetDetection*     m_COnsetDetection = 0;
    Sequencer*          m_CSequencer = 0;
    float               m_gain = 1;
    float               m_smoothGain = 0;

private:

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NosyAspirationAudioProcessor)
};
