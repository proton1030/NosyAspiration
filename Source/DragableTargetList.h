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
        return numRows;
    }
    
    void paintListBoxItem (int rowNumber, Graphics& g,
                           int width, int height, bool rowIsSelected) override
    {
        g.setColour(Colour::fromFloatRGBA (1.0f, 0.0f, 0.0f, 0.0f));
        g.setFont(getFont());
        g.setFont (24);
        g.setColour (Colour::fromRGB(176, 59, 82));
        g.drawRoundedRectangle(8, 8, width-16, height-16, 5.0, 3.0);
        g.setColour (Colours::lightgrey);
        g.drawText (wordList[rowNumber],
                    0, 0, width, height,
                    Justification::centred, true);
        
        if (rowIsSelected)
        {
            g.setColour (Colour::fromRGBA(176, 59, 82, 45));
            g.fillRoundedRectangle(8, 8, width-16, height-16, 5.0);
            
        }
    }
    
    var getDragSourceDescription (const SparseSet<int>& selectedRows) override
    {
        StringArray rows;
        
        for (int i = 0; i < selectedRows.size(); ++i)
            rows.add (String (selectedRows[i] + 1));
        
        
        numRows++;
        return rows.joinIntoString (", ");
    }
    
    const Font& getFont()
    {
        static Font wacky (Font (Typeface::createSystemTypefaceFor (BinaryData::omnessemiboldwebfont_ttf, BinaryData::omnessemiboldwebfont_ttfSize)));
        return wacky;
    }
    
    int numRows = 0;
    vector<string> wordList;
    
};
