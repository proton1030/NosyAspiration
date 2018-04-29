/*
  ==============================================================================

    Sequencer.cpp
    Created: 28 Apr 2018 9:06:37am
    Author:  zhao yan

  ==============================================================================
*/

#include "Sequencer.h"
Sequencer::Sequencer(float sampleRate, float blockLength):
curPronounciation(0),
curPronunceationIdx(0),
sampleRate(sampleRate),
blockLength(blockLength)
{
    
}
Sequencer::~Sequencer()
{
    
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
    la.params[0][Tract::k_tongueTipIndex] = 0.02;
    la.params[0][Tract::k_tongueBaseIndex] = 0.02;
    la.params[0][Tract::k_tongueTipDiameter] = 12;
    la.params[0][Tract::k_tongueBaseDiameter] = 12;
    la.params[1][Tract::k_tongueTipIndex] = 0.2;
    la.params[1][Tract::k_tongueBaseIndex] = 0.2;
    la.params[1][Tract::k_tongueTipDiameter] = 5;
    la.params[1][Tract::k_tongueBaseDiameter] = 6;
    la.duration = new float[la.numOfVowels];
    la.duration[0] = 100.0f;
    la.duration[1] = -1;
    
    pronunciation li;
    li.name = "li";
    li.numOfVowels = 2;
    li.params = new float*[li.numOfVowels];
    for (int i = 0; i < li.numOfVowels; i++) {
        li.params[i] = new float[Tract::k_num_tract_params];
    }
    li.params[0][Tract::k_tongueTipIndex] = 0.02;
    li.params[0][Tract::k_tongueBaseIndex] = 0.02;
    li.params[0][Tract::k_tongueTipDiameter] = 12;
    li.params[0][Tract::k_tongueBaseDiameter] = 12;
    li.params[1][Tract::k_tongueTipIndex] = 0.2;
    li.params[1][Tract::k_tongueBaseIndex] = 0.2;
    li.params[1][Tract::k_tongueTipDiameter] = 5;
    li.params[1][Tract::k_tongueBaseDiameter] = 6;
    li.duration = new float[la.numOfVowels];
    li.duration[0] = 100.0f;
    li.duration[1] = -1;
    
    availableElements.push_back("la");
    availableElements.push_back("li");
    pronunciationLookUp["la"] = la;
    pronunciationLookUp["li"] = li;
}

float* Sequencer::incPronunceAndGetVowel() {
    if (curSequence.size() > 0){
        curPronounciation = &curSequence[curPronunceationIdx];
        curPronunceationIdx = (curPronunceationIdx + 1) % curSequence.size();
        return curPronounciation->params[0];
    } else {
        return 0;
    }
    
}

float* Sequencer::incVowelAndGetVowel() {
    if (curPronounciation != 0) {
        onsetTime += timeStep;
        if (onsetTime >= curPronounciation->duration[curVowelIdx] && curPronounciation->duration[curVowelIdx] < 0) {
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

vector<string> Sequencer::getAvailableElements(){
    return availableElements;
}

