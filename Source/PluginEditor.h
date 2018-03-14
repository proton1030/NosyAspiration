/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class NosyAspirationAudioProcessorEditor  : public AudioProcessorEditor,
                                            public Slider::Listener
{
public:
    NosyAspirationAudioProcessorEditor (NosyAspirationAudioProcessor&);
    ~NosyAspirationAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NosyAspirationAudioProcessor& processor;
    
    ScopedPointer<Slider> sliderFreq, sliderTonguePos, sliderTongueDiam;
    ScopedPointer<Label> lSliderFreq, lSliderTonguePos, lSliderTongueDiam;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NosyAspirationAudioProcessorEditor)
};
