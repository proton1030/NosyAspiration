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
#include "DragableTargetList.h"
#include "Sequencer.h"
#include <iostream>


class DragableTarget  : public Component, public DragAndDropTarget
{
public:
    DragableTarget()
    {
        
    }
    
    ~DragableTarget(){}
    // The following methods implement the necessary virtual functions from ListBoxModel,
    // telling the listbox how many rows there are, painting them, etc.
    
    void resized() override
    {
        
    }
    
    void paint (Graphics& g) override
    {
//        g.fillAll(Colours::red);
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
    
    
    var getDragSourceDescription (const SparseSet<int>& selectedRows)
    {
        StringArray rows;
        
        for (int i = 0; i < selectedRows.size(); ++i)
            rows.add (String (selectedRows[i] + 1));
        
        return rows.joinIntoString (", ");
    }
    
    void getTargetModel(DragableTargetList &model, ListBox &listB, ListBox &listSource, Sequencer &seq)
    {
        targetM = &model;
        listM = &listB;
        listSourceM = &listSource;
        seqM = &seq;
    }
    
    const Font& getFont()
    {
        static Font wacky (Font (Typeface::createSystemTypefaceFor (BinaryData::omnessemiboldwebfont_ttf, BinaryData::omnessemiboldwebfont_ttfSize)));
        return wacky;
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
//        message = "Items dropped: " + dragSourceDetails.description.toString();
        //        m_iActiveWords ++;
//        activeWords.add(new WordListItem());

        if (dragSourceDetails.sourceComponent.get() == listSourceM)
        {
            String name = dragSourceDetails.description.toString();
            seqM->Add(name.toStdString());
            targetM->wordList.push_back(name.toStdString());
        }
        else
        {
            targetM->wordList.erase(targetM->wordList.begin() + targetM->activeRowNum);
            seqM->deleteNote(targetM->activeRowNum);
        }
        listM->updateContent();
        listM->repaint();
        somethingIsBeingDraggedOver = false;
        repaint();
    }
    
private:
    String message  {""};
    bool somethingIsBeingDraggedOver = false;
    
    
    DragableTargetList*     targetM = 0;
    ListBox*                listM = 0;
    ListBox*                listSourceM = 0;
    Sequencer*              seqM = 0;
};

