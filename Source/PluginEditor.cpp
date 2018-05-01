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
    target.getTargetModel(targetModel, targetListBox, sourceListBox, *processor.m_CSequencer);
    
    addAndMakeVisible (knobGain = new Slider ("gain"));
    knobGain->setRange (0, 1, 0.02);
    knobGain->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    knobGain->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    
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
    knobVibrato->onValueChange = [this] {
        processor.m_CGlottis->setParam(Glottis::k_vibrato_freq, knobVibrato->getValue());
    };
    
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
    knobGain->setBounds (230, 400, 120, 120);
    knobVibrato->setBounds (450, 400, 120, 120);
//    target.getViewport()->setTransform(AffineTransform::rotation(3.2));
}

const Font& NosyAspirationAudioProcessorEditor::getFont()
{
    static Font wacky (Font (Typeface::createSystemTypefaceFor (BinaryData::omnessemiboldwebfont_ttf,
                                                                BinaryData::omnessemiboldwebfont_ttfSize)));
    return wacky;
}
