/*
  ==============================================================================

    Sequencer.cpp
    Created: 28 Apr 2018 9:06:37am
    Author:  zhao yan

  ==============================================================================
*/

#include "Sequencer.h"
#include <iostream>
Sequencer::Sequencer(float sampleRate, float blockLength):
curPronounciation(0),
curPronunceationIdx(0),
curVowelIdx(0),
sampleRate(sampleRate),
blockLength(blockLength)
{
    
}
Sequencer::~Sequencer()
{
    for (vector<pronunciation>::iterator it = curSequence.begin(); it != curSequence.end(); it++) {
        for (int i = 0; i < it->numOfVowels; i++) {
            delete [] it->params[i];
        }
        delete [] it->params;
    }
}
void Sequencer::init() {
    timeStep = blockLength/sampleRate * 1000;
    
    pronunciation la;
    la.name = "la";
    la.numOfVowels = 2;
    la.params = new float*[la.numOfVowels];
    for (int i = 0; i < la.numOfVowels; i++) {
        la.params[i] = new float[Tract::k_num_tract_params];
    }
    
    la.params[0][Tract::k_tongueBaseIndex] = 13.58;
    la.params[0][Tract::k_tongueBaseDiameter] = 2.9;
    la.params[0][Tract::k_tongueTipIndex] = 40.45;
    la.params[0][Tract::k_tongueTipDiameter] = 0.88;
    
    la.params[1][Tract::k_tongueBaseIndex] = 13.58;
    la.params[1][Tract::k_tongueBaseDiameter] = 2.9;
    la.params[1][Tract::k_tongueTipIndex] = 40.45;
    la.params[1][Tract::k_tongueTipDiameter] = 2.33;
    
    la.duration = new float[la.numOfVowels];
    la.duration[0] = 800.0f;
    la.duration[1] = -1;
    
    pronunciation li;
    li.name = "li";
    li.numOfVowels = 2;
    li.params = new float*[li.numOfVowels];
    for (int i = 0; i < li.numOfVowels; i++) {
        li.params[i] = new float[Tract::k_num_tract_params];
    }
    
    li.params[0][Tract::k_tongueBaseIndex] = 7.8;
    li.params[0][Tract::k_tongueBaseDiameter] = 2.61;
    li.params[0][Tract::k_tongueTipIndex] = 40.45;
    li.params[0][Tract::k_tongueTipDiameter] = 0.51;
    
    li.params[1][Tract::k_tongueBaseIndex] = 31.98;
    li.params[1][Tract::k_tongueBaseDiameter] = 2.52;
    li.params[1][Tract::k_tongueTipIndex] = 42;
    li.params[1][Tract::k_tongueTipDiameter] = 2.5;
    
    li.duration = new float[li.numOfVowels];
    li.duration[0] = 800.0f;
    li.duration[1] = -1;
    
    availablePronunciations.push_back("la");
    availablePronunciations.push_back("li");
    pronunciationLookUp["la"] = la;
    pronunciationLookUp["li"] = li;
    Add("la");
    Add("li");
}

float* Sequencer::incPronunceAndGetVowel() {
    if (curSequence.size() > 0){
        curPronounciation = &curSequence[curPronunceationIdx];
        curPronunceationIdx = (curPronunceationIdx + 1) % curSequence.size();
        curVowelIdx = 0;
        std::cout << curPronounciation->name << std::endl;
        return curPronounciation->params[0];
    } else {
        return 0;
    }
    
}

float* Sequencer::incVowelAndGetVowel() {
    if (curPronounciation != 0) {
        onsetTime += timeStep;
        if (onsetTime >= curPronounciation->duration[curVowelIdx] && curPronounciation->duration[curVowelIdx] > 0) {
            curVowelIdx++;
        }
        return curPronounciation->params[curVowelIdx];
    } else {
        return 0;
    }
}


void Sequencer::Add(string pronouciation) {
    curSequence.push_back(pronunciationLookUp[pronouciation]);
    curPronunceationIdx = 0;
}

// pos is zero based
void Sequencer::insert(string pronounciation, int pos) {
    curSequence.insert(curSequence.begin() + pos, pronunciationLookUp[pronounciation]);
    curPronunceationIdx = 0;
}

// pos is zero based
void Sequencer::deleteNote(int pos) {
    curSequence.erase(curSequence.begin() + pos);
    curPronunceationIdx = 0;
}

vector<string> Sequencer::getAvailablePronunciations(){
    return availablePronunciations;
}

