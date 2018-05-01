/*
  ==============================================================================

    DragableTargetList.h
    Created: 30 Apr 2018 10:36:17pm
    Author:  Hanyu Liu

  ==============================================================================
*/

#pragma once
#include <vector>
#include <string>


struct DragableTargetList  : public ListBoxModel
{
    // The following methods implement the necessary virtual functions from ListBoxModel,
    // telling the listbox how many rows there are, painting them, etc.
    int getNumRows() override
    {
        return int(wordList.size());
    }
    
    void paintListBoxItem (int rowNumber, Graphics& g,
                           int width, int height, bool rowIsSelected) override
    {

        
        g.setColour(Colour::fromFloatRGBA (1.0f, 0.0f, 0.0f, 0.0f));
        g.setFont(getFont());
        g.setFont (24);
        g.setColour (Colours::lightgrey);
        g.drawRoundedRectangle(8, 8, width-16, height-16, 5.0, 3.0);
        
        g.setColour (Colours::lightgrey);
        g.drawText (wordList[rowNumber],
                    0, 0, width, height,
                    Justification::centred, true);
        if (rowIsSelected)
        {
            g.setColour (Colour::fromRGBA(206, 59, 82, 135));
            g.fillRoundedRectangle(8, 8, width-16, height-16, 5.0);
        }
        if (rowNumber == highlightRowNum && int(wordList.size()) != 0)
        {
            g.setColour (Colours::lightgrey);
            g.fillRoundedRectangle(8, 8, width-16, height-16, 5.0);
            g.setColour (Colours::darkgrey);
            g.drawText (wordList[rowNumber],
                        0, 0, width, height,
                        Justification::centred, true);
        }
    }
    
    var getDragSourceDescription (const SparseSet<int>& selectedRows) override
    {
        activeRowNum = selectedRows[0];
        return String(wordList[selectedRows[0]]);
    }
    
    const Font& getFont()
    {
        static Font wacky (Font (Typeface::createSystemTypefaceFor (BinaryData::Chalkduster_ttf, BinaryData::Chalkduster_ttfSize)));
        return wacky;
    }
    
    void getCurrentSequence(vector<string> words)
    {
        wordList = words;
    }
    
    vector<string> wordList;
    int activeRowNum = 0;
    int highlightRowNum = 0;
};
