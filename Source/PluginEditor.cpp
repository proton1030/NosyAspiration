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
    
    
    addAndMakeVisible (sliderFreq = new Slider ("Frequency"));
    sliderFreq->setRange (40, 600, 0.01);
    sliderFreq->setSliderStyle (Slider::LinearHorizontal);
    sliderFreq->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
    sliderFreq->addListener (this);
    
    addAndMakeVisible (sliderTonguePos = new Slider ("Tongue Position"));
    sliderTonguePos->setRange (1, 30, 0.01);
    sliderTonguePos->setSliderStyle (Slider::LinearHorizontal);
    sliderTonguePos->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
    sliderTonguePos->addListener (this);
    
    addAndMakeVisible (sliderTongueDiam = new Slider ("Tongue Position"));
    sliderTongueDiam->setRange (2.05, 3.05, 0.01);
    sliderTongueDiam->setSliderStyle (Slider::LinearHorizontal);
    sliderTongueDiam->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
    sliderTongueDiam->addListener (this);
    
    addAndMakeVisible (lSliderFreq = new Label ("new label", TRANS("Frequency")));
    lSliderFreq->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lSliderFreq->setJustificationType (Justification::centredLeft);
    lSliderFreq->setEditable (false, false, false);
    lSliderFreq->setColour (TextEditor::textColourId, Colours::black);
    lSliderFreq->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (lSliderTonguePos = new Label ("new label", TRANS("Tongue Base Loc")));
    lSliderTonguePos->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lSliderTonguePos->setJustificationType (Justification::centredLeft);
    lSliderTonguePos->setEditable (false, false, false);
    lSliderTonguePos->setColour (TextEditor::textColourId, Colours::black);
    lSliderTonguePos->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (lSliderTongueDiam = new Label ("new label", TRANS("Tongue Base Height")));
    lSliderTongueDiam->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lSliderTongueDiam->setJustificationType (Justification::centredLeft);
    lSliderTongueDiam->setEditable (false, false, false);
    lSliderTongueDiam->setColour (TextEditor::textColourId, Colours::black);
    lSliderTongueDiam->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    sliderFreq->setValue(processor.m_CGlottis->getParam(Glottis::k_frequency));
    sliderTonguePos->setValue(processor.m_CTract->getParam(Tract::k_tongueBaseIndex));
    sliderTongueDiam->setValue(processor.m_CTract->getParam(Tract::k_tongueBaseDiameter));
    
    setSize (500, 300);
}

NosyAspirationAudioProcessorEditor::~NosyAspirationAudioProcessorEditor()
{
    sliderFreq = nullptr;
    sliderTonguePos = nullptr;
    sliderTongueDiam = nullptr;
    lSliderFreq = nullptr;
    lSliderTonguePos = nullptr;
    lSliderTongueDiam = nullptr;
}

//==============================================================================
void NosyAspirationAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    
}

void NosyAspirationAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    lSliderFreq->setBounds (proportionOfWidth (0.020f), proportionOfHeight (0.1000f), proportionOfWidth (0.20f), proportionOfHeight (0.1000f));
    lSliderTonguePos->setBounds (proportionOfWidth (0.020f), proportionOfHeight (0.2500f), proportionOfWidth (0.20f), proportionOfHeight (0.1000f));
    lSliderTongueDiam->setBounds (proportionOfWidth (0.020f), proportionOfHeight (0.400f), proportionOfWidth (0.20f), proportionOfHeight (0.1000f));
    sliderFreq->setBounds (proportionOfWidth (0.23f), proportionOfHeight (0.1000f), proportionOfWidth (0.720f), proportionOfHeight (0.1000f));
    sliderTonguePos->setBounds (proportionOfWidth (0.23f), proportionOfHeight (0.2500f), proportionOfWidth (0.720f), proportionOfHeight (0.1000f));
    sliderTongueDiam->setBounds (proportionOfWidth (0.23f), proportionOfHeight (0.4000f), proportionOfWidth (0.720f), proportionOfHeight (0.1000f));
}

void NosyAspirationAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == sliderFreq)
    {
        processor.m_CGlottis->setParam(Glottis::k_frequency, sliderThatWasMoved->getValue());
    }
    else if (sliderThatWasMoved == sliderTonguePos)
    {
        processor.m_CTract->setParam(Tract::k_tongueBaseIndex, sliderThatWasMoved->getValue());
    }
    else if (sliderThatWasMoved == sliderTongueDiam)
    {
        processor.m_CTract->setParam(Tract::k_tongueBaseDiameter, sliderThatWasMoved->getValue());
    }
}
