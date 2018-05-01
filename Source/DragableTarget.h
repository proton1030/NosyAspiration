/*
  ==============================================================================

    DragableTarget.h
    Created: 30 Apr 2018 12:16:59am
    Author:  Hanyu Liu

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "WordListItem.h"

class DragableTarget :
public DragAndDropTarget,
public ListBox,
public ListBoxModel
{
public:
    DragableTarget()
    {
        m_iActiveWords = 5;
        
        wordList.setModel (this);
        wordList.setRowHeight(10);
        addAndMakeVisible(wordList);
//        wordList.setModel(this);
//        wordList.setRowHeight(30);
//        listBox.selectRow(iRowSelection);
//        listBox.setRowSelectedOnMouseDown(true);
    }
    
    ~DragableTarget()
    {
        
    }
    
    void resized() override
    {
//        wordList.setBounds (getLocalBounds().reduced(10));
    }
    
    void paint (Graphics& g) override
    {
        if (somethingIsBeingDraggedOver)
        {
            g.setColour (Colours::hotpink);
            g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 15.0, 6.0);
        }
        
        g.setColour (getLookAndFeel().findColour (Label::textColourId));
        g.setFont (getFont());
        g.setFont (20.0f);
        g.drawFittedText (message, getLocalBounds().reduced (10, 0), Justification::centred, 4);
    }
    
    int getNumRows() override
    {
//        return m_iActiveWords;
        return activeWords.size();
    }
    
    void paintListBoxItem (int rowNumber,
                           Graphics& g,
                           int width, int height,
                           bool rowIsSelected) override
    {
        g.setColour(Colour::fromFloatRGBA (1.0f, 0.0f, 0.0f, 0.0f));
        g.setFont(getFont());
        g.setFont (24);
        g.setColour (Colour::fromRGB(176, 59, 82));
        g.drawRoundedRectangle(8, 8, width-16, height-16, 5.0, 3.0);
        g.setColour (Colours::lightgrey);
        g.drawText ("Thing #" + String (rowNumber + 1),
                    0, 0, width, height,
                    Justification::centred, true);
    }
    
    Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate) override
    {
        WordListItem *row = static_cast<WordListItem*>(existingComponentToUpdate);
        if(rowNumber < activeWords.size())
        {
            if(!row)
                row = new WordListItem();

            if(isRowSelected)
            {
                row->isHighlighted = true;
            }
            else{
                row->isHighlighted = false;
            }

        }
        else
        {
            delete existingComponentToUpdate;
            row = nullptr;
        }

        return row;
    }
    
    bool isInterestedInDragSource (const SourceDetails& /*dragSourceDetails*/) override
    {
        // normally you'd check the sourceDescription value to see if it's the
        // sort of object that you're interested in before returning true, but for
        // the demo, we'll say yes to anything..
        return true;
    }
    
    void itemDragEnter (const SourceDetails& /*dragSourceDetails*/) override
    {
        somethingIsBeingDraggedOver = true;
        repaint();
    }
    
    void itemDragMove (const SourceDetails& /*dragSourceDetails*/) override
    {
    }
    
    void itemDragExit (const SourceDetails& /*dragSourceDetails*/) override
    {
        somethingIsBeingDraggedOver = false;
        repaint();
    }
    
    void itemDropped (const SourceDetails& dragSourceDetails) override
    {
        message = "Items dropped: " + dragSourceDetails.description.toString();
//        m_iActiveWords ++;
        activeWords.add(new WordListItem());
        
        somethingIsBeingDraggedOver = false;
        repaint();
    }
    
    
private:
    String message  {""};
    bool somethingIsBeingDraggedOver = false;
    
    ListBox                     wordList;
    OwnedArray<WordListItem>    activeWords;
    
    int m_iActiveWords;
    
    const Font& getFont()
    {
        static Font wacky (Font (Typeface::createSystemTypefaceFor (BinaryData::omnessemiboldwebfont_ttf, BinaryData::omnessemiboldwebfont_ttfSize)));
        return wacky;
    }
    
};
