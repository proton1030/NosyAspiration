/*
  ==============================================================================

    WordListItem.h
    Created: 28 Apr 2018 2:23:55pm
    Author:  Hanyu Liu

  ==============================================================================
*/

#pragma once

class WordListItem : public Component, public DragAndDropContainer
{
public:
    WordListItem()
    {
        addAndMakeVisible(m_Label = new Label("test", TRANS("test")));
    };
    
    ~WordListItem()
    {
        
    };
    
    void resized() override
    {
        m_Label->setBounds(0, 0, proportionOfWidth(0.2), proportionOfHeight(1));
    };
    
    void paint(Graphics& g) override
    {
        if (isHighlighted)
        {
            g.fillAll(Colours::lightblue);
        }
        else
        {
            g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
        }
        g.setFont (Font (16.0f));
        g.setColour (Colours::white);
    };
    
    bool isHighlighted;
    
private:
    ScopedPointer<Label> m_Label;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WordListItem)
};
