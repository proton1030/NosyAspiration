/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "DragableSource.h"
#include "DragableTarget.h"


//==============================================================================
/**
*/
class NosyAspirationAudioProcessorEditor  : public AudioProcessorEditor,
                                            public Slider::Listener,
                                            public DragAndDropContainer
{
public:
    NosyAspirationAudioProcessorEditor (NosyAspirationAudioProcessor&);
    ~NosyAspirationAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    static const Font& getFont();
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NosyAspirationAudioProcessor& processor;
    ListBox sourceListBox  { "D+D source", nullptr };
    DragableSource sourceModel;
    DragableTarget target;
    
    
    ScopedPointer<Slider> sliderFreq, sliderTonguePos, sliderTongueDiam, sliderTongueTipPos, sliderTongueTipDiam;
    ScopedPointer<Label> lSliderFreq, lSliderTonguePos, lSliderTongueDiam, lSliderTongueTipPos, lSliderTongueTipDiam;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NosyAspirationAudioProcessorEditor)
};
