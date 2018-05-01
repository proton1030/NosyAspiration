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


class DragableTarget  : public Component, public DragAndDropTarget, public Timer
{
public:
    DragableTarget()
    {
        startTimer (100);
    }
    
    ~DragableTarget()
    {
        
    }
    // The following methods implement the necessary virtual functions from ListBoxModel,
    // telling the listbox how many rows there are, painting them, etc.
    
    void resized() override
    {
        
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
    
    
    var getDragSourceDescription (const SparseSet<int>& selectedRows)
    {
        StringArray rows;
        
        for (int i = 0; i < selectedRows.size(); ++i)
            rows.add (String (selectedRows[i] + 1));
        
        return rows.joinIntoString (", ");
    }
    
    void getTargetModel(DragableTargetList &model, ListBox &listB, ListBox &listSource, Sequencer &seq, NosyAspirationAudioProcessor& processor)
    {
        targetM = &model;
        listM = &listB;
        listSourceM = &listSource;
        seqM = &seq;
        processorM = &processor;
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
        
        somethingIsBeingDraggedOver = false;
        repaint();
    }
    
private:
    void timerCallback() override
    {
        targetM->highlightRowNum = processorM->m_CSequencer->getCurrentPronounciationIdx();
        listM->updateContent();
        listM->repaint();
    }
    
    String message  {""};
    bool somethingIsBeingDraggedOver = false;
    
    
    DragableTargetList*     targetM = 0;
    ListBox*                listM = 0;
    ListBox*                listSourceM = 0;
    Sequencer*              seqM = 0;
    NosyAspirationAudioProcessor* processorM = 0;
};

