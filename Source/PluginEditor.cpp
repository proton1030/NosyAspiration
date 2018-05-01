/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
NosyAspirationAudioProcessorEditor::NosyAspirationAudioProcessorEditor (NosyAspirationAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    sourceModel.getWordsInfo(processor.m_CSequencer->getAvailablePronunciations());
    targetModel.getCurrentSequence(processor.m_CSequencer->getCurrentPronunciations());
    
    sourceListBox.setModel (&sourceModel);
    sourceListBox.setRowHeight(90);
    sourceListBox.setOpaque(true);
    sourceListBox.setColour(ListBox::ColourIds::backgroundColourId , Colour::fromFloatRGBA (1.0f, 0.0f, 0.0f, 0.0f));
    sourceListBox.getViewport()->setScrollBarsShown(false, false, true, true);

    targetListBox.setModel (&targetModel);
    targetListBox.setRowHeight(90);
    targetListBox.setOpaque(true);
    targetListBox.setColour(ListBox::ColourIds::backgroundColourId , Colour::fromFloatRGBA (1.0f, 0.0f, 0.0f, 0.0f));
    targetListBox.getViewport()->setScrollBarsShown(false, false, true, true);

    
    addAndMakeVisible (sourceListBox);
    addAndMakeVisible (targetListBox);
    addAndMakeVisible (target);
    target.getTargetModel(targetModel, targetListBox, sourceListBox, *processor.m_CSequencer, processor);
    
    addAndMakeVisible (knobGain = new Slider ("gain"));
    knobGain->setRange (0, 1, 0.02);
    knobGain->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    knobGain->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    knobGain->setValue(processor.m_gain);
    
    knobGain->setColour(Slider::ColourIds::thumbColourId, Colours::lightpink);
    knobGain->setColour(Slider::ColourIds::trackColourId, Colours::white);
    knobGain->setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::lightgrey);
    knobGain->onValueChange = [this] {
        processor.m_gain = knobGain->getValue();
    };
    
    addAndMakeVisible (knobVibrato = new Slider ("vibrato"));
    knobVibrato->setRange (0, 8, 0.1);
    knobVibrato->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    knobVibrato->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    knobVibrato->setValue(processor.m_CGlottis->getParam(Glottis::k_vibrato_freq));
    
    knobVibrato->setColour(Slider::ColourIds::thumbColourId, Colours::lightpink);
    knobVibrato->setColour(Slider::ColourIds::trackColourId, Colours::white);
    knobVibrato->setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::lightgrey);
    knobVibrato->onValueChange = [this] {
        processor.m_CGlottis->setParam(Glottis::k_vibrato_freq, knobVibrato->getValue());
    };
    
    addAndMakeVisible (knobReverb = new Slider ("reverb"));
    knobReverb->setRange (0, 1, 0.01);
    knobReverb->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    knobReverb->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    knobReverb->setValue(processor.m_reverbDryWet);
    
    knobReverb->setColour(Slider::ColourIds::thumbColourId, Colours::lightpink);
    knobReverb->setColour(Slider::ColourIds::trackColourId, Colours::white);
    knobReverb->setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::lightgrey);
    knobReverb->onValueChange = [this] {
        processor.m_reverbDryWet = knobReverb->getValue();
    };
    
    targetListBox.updateContent();
    
    setSize (800, 600);
}

NosyAspirationAudioProcessorEditor::~NosyAspirationAudioProcessorEditor()
{

}

//==============================================================================
void NosyAspirationAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    Image background = ImageCache::getFromMemory(BinaryData::background_jpg, BinaryData::background_jpgSize);
    g.drawImageAt (background, 0, 0);
    
    g.setColour (Colours::white);
    g.setFont (15.0f);
    
}

void NosyAspirationAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto r = getLocalBounds().reduced (8);
    sourceListBox.setBounds (630, 190, 130, 380);
    targetListBox.setBounds(40, 190, 130, 380);
    target.setBounds (300, 180, 200, 200);
    knobGain->setBounds (210, 450, 100, 100);
    knobVibrato->setBounds (350, 390, 100, 100);
    knobReverb->setBounds (480, 430, 100, 100);
//    target.getViewport()->setTransform(AffineTransform::rotation(3.2));
   
}

const Font& NosyAspirationAudioProcessorEditor::getFont()
{
    static Font wacky (Font (Typeface::createSystemTypefaceFor (BinaryData::omnessemiboldwebfont_ttf,
        BinaryData::omnessemiboldwebfont_ttfSize)));
    return wacky;
}
