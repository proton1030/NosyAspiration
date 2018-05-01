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
    
//    targetModel.numRows = 1;
    targetListBox.setModel (&targetModel);
    targetListBox.setRowHeight(40);
    targetListBox.setOpaque(true);
    targetListBox.setColour(ListBox::ColourIds::backgroundColourId , Colour::fromFloatRGBA (1.0f, 0.0f, 0.0f, 0.0f));
    
    addAndMakeVisible (sourceListBox);
    addAndMakeVisible (targetListBox);
    addAndMakeVisible (target);
    target.getTargetModel(targetModel, targetListBox, *processor.m_CSequencer);
    
    
    
//    addAndMakeVisible (sliderFreq = new Slider ("Frequency"));
//    sliderFreq->setRange (40, 600, 0.01);
//    sliderFreq->setSliderStyle (Slider::LinearHorizontal);
//    sliderFreq->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
//    sliderFreq->addListener (this);
//
//    addAndMakeVisible (sliderTonguePos = new Slider ("Tongue Position"));
//    sliderTonguePos->setRange (1, 40, 0.01);
//    sliderTonguePos->setSliderStyle (Slider::LinearHorizontal);
//    sliderTonguePos->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
//    sliderTonguePos->addListener (this);
//
//    addAndMakeVisible (sliderTongueDiam = new Slider ("Tongue Position"));
//    sliderTongueDiam->setRange (2.05, 3.05, 0.01);
//    sliderTongueDiam->setSliderStyle (Slider::LinearHorizontal);
//    sliderTongueDiam->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
//    sliderTongueDiam->addListener (this);
//
//    addAndMakeVisible (sliderTongueTipPos = new Slider ("Tongue Tip Position"));
//    sliderTongueTipPos->setRange (10, 42, 0.01);
//    sliderTongueTipPos->setSliderStyle (Slider::LinearHorizontal);
//    sliderTongueTipPos->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
//    sliderTongueTipPos->addListener (this);
//
//    addAndMakeVisible (sliderTongueTipDiam = new Slider ("Tongue Position"));
//    sliderTongueTipDiam->setRange (-1.05, 3.05, 0.01);
//    sliderTongueTipDiam->setSliderStyle (Slider::LinearHorizontal);
//    sliderTongueTipDiam->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
//    sliderTongueTipDiam->addListener (this);
//
//    addAndMakeVisible (lSliderFreq = new Label ("new label", TRANS("Frequency")));
//    lSliderFreq->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
//    lSliderFreq->setJustificationType (Justification::centredLeft);
//    lSliderFreq->setEditable (false, false, false);
//    lSliderFreq->setColour (TextEditor::textColourId, Colours::black);
//    lSliderFreq->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
//
//    addAndMakeVisible (lSliderTonguePos = new Label ("new label", TRANS("Tongue Base Loc")));
//    lSliderTonguePos->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
//    lSliderTonguePos->setJustificationType (Justification::centredLeft);
//    lSliderTonguePos->setEditable (false, false, false);
//    lSliderTonguePos->setColour (TextEditor::textColourId, Colours::black);
//    lSliderTonguePos->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
//
//    addAndMakeVisible (lSliderTongueDiam = new Label ("new label", TRANS("Tongue Base Height")));
//    lSliderTongueDiam->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
//    lSliderTongueDiam->setJustificationType (Justification::centredLeft);
//    lSliderTongueDiam->setEditable (false, false, false);
//    lSliderTongueDiam->setColour (TextEditor::textColourId, Colours::black);
//    lSliderTongueDiam->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
//
//    addAndMakeVisible (lSliderTongueTipPos = new Label ("new label", TRANS("Tongue Base Loc")));
//    lSliderTongueTipPos->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
//    lSliderTongueTipPos->setJustificationType (Justification::centredLeft);
//    lSliderTongueTipPos->setEditable (false, false, false);
//    lSliderTongueTipPos->setColour (TextEditor::textColourId, Colours::black);
//    lSliderTongueTipPos->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
//
//    addAndMakeVisible (lSliderTongueTipDiam = new Label ("new label", TRANS("Tongue Base Height")));
//    lSliderTongueTipDiam->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
//    lSliderTongueTipDiam->setJustificationType (Justification::centredLeft);
//    lSliderTongueTipDiam->setEditable (false, false, false);
//    lSliderTongueTipDiam->setColour (TextEditor::textColourId, Colours::black);
//    lSliderTongueTipDiam->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
//
//    sliderFreq->setValue(processor.m_CGlottis->getParam(Glottis::k_frequency));
//    sliderTonguePos->setValue(processor.m_CTract->getParam(Tract::k_tongueBaseIndex));
//    sliderTongueDiam->setValue(processor.m_CTract->getParam(Tract::k_tongueBaseDiameter));
//    sliderTongueTipPos->setValue(processor.m_CTract->getParam(Tract::k_tongueTipIndex));
//    sliderTongueTipDiam->setValue(processor.m_CTract->getParam(Tract::k_tongueTipDiameter));
    
    setSize (800, 600);
}

NosyAspirationAudioProcessorEditor::~NosyAspirationAudioProcessorEditor()
{
    sliderFreq = nullptr;
    sliderTonguePos = nullptr;
    sliderTongueDiam = nullptr;
    sliderTongueTipPos = nullptr;
    sliderTongueTipDiam = nullptr;
    lSliderFreq = nullptr;
    lSliderTonguePos = nullptr;
    lSliderTongueDiam = nullptr;
    lSliderTongueTipPos = nullptr;
    lSliderTongueTipDiam = nullptr;
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
    
//    lSliderFreq->setBounds (proportionOfWidth (0.020f), proportionOfHeight (0.1000f), proportionOfWidth (0.20f), proportionOfHeight (0.1000f));
//    lSliderTonguePos->setBounds (proportionOfWidth (0.020f), proportionOfHeight (0.2500f), proportionOfWidth (0.20f), proportionOfHeight (0.1000f));
//    lSliderTongueDiam->setBounds (proportionOfWidth (0.020f), proportionOfHeight (0.400f), proportionOfWidth (0.20f), proportionOfHeight (0.1000f));
//    lSliderTongueTipPos->setBounds (proportionOfWidth (0.020f), proportionOfHeight (0.5500f), proportionOfWidth (0.20f), proportionOfHeight (0.1000f));
//    lSliderTongueTipDiam->setBounds (proportionOfWidth (0.020f), proportionOfHeight (0.700f), proportionOfWidth (0.20f), proportionOfHeight (0.1000f));
//    sliderFreq->setBounds (proportionOfWidth (0.23f), proportionOfHeight (0.1000f), proportionOfWidth (0.720f), proportionOfHeight (0.1000f));
//    sliderTonguePos->setBounds (proportionOfWidth (0.23f), proportionOfHeight (0.2500f), proportionOfWidth (0.720f), proportionOfHeight (0.1000f));
//    sliderTongueDiam->setBounds (proportionOfWidth (0.23f), proportionOfHeight (0.4000f), proportionOfWidth (0.720f), proportionOfHeight (0.1000f));
//    sliderTongueTipPos->setBounds (proportionOfWidth (0.23f), proportionOfHeight (0.5500f), proportionOfWidth (0.720f), proportionOfHeight (0.1000f));
//    sliderTongueTipDiam->setBounds (proportionOfWidth (0.23f), proportionOfHeight (0.7000f), proportionOfWidth (0.720f), proportionOfHeight (0.1000f));
    auto r = getLocalBounds().reduced (8);
    sourceListBox.setBounds (630, 190, 130, 380);
    targetListBox.setBounds(30, 180, 550, 120);
    target      .setBounds (30, 480, 550, 120);
//    target.getViewport()->setTransform(AffineTransform::rotation(3.2));
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
    else if (sliderThatWasMoved == sliderTongueTipPos)
    {
        processor.m_CTract->setParam(Tract::k_tongueTipIndex, sliderThatWasMoved->getValue());
    }
    else if (sliderThatWasMoved == sliderTongueTipDiam)
    {
        processor.m_CTract->setParam(Tract::k_tongueTipDiameter, sliderThatWasMoved->getValue());
    }
}

const Font& NosyAspirationAudioProcessorEditor::getFont()
{
    static Font wacky (Font (Typeface::createSystemTypefaceFor (BinaryData::omnessemiboldwebfont_ttf,
                                                                BinaryData::omnessemiboldwebfont_ttfSize)));
    return wacky;
}
