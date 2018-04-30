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
        delete [] it->duration;
    }
}

//adding in prounciation params
void Sequencer::init() {
    timeStep = blockLength/sampleRate * 1000;
    
    float la_params[2][Tract::k_num_tract_params] =
    {
        {13.58, 2.9, 40.45, 0.88},
        {13.58, 2.9, 40.45, 2.33}
    };
    float la_duration[2] = {800.0f, -1};
    addPronunciation("la", 2, la_duration, la_params);
    
    float li_params[2][Tract::k_num_tract_params] =
    {
        {7.8, 2.61, 40.45, 0.51},
        {31.98, 2.52, 42, 2.5}
    };
    float li_duration[2] = {800.0f, -1};
    addPronunciation("li", 2, li_duration, li_params);

    Add("la");
    Add("li");
}
// make it easy to add hardcoded pronunciations
void Sequencer::addPronunciation(string name, int numOfVowels, float *durationInMs, float params[][Tract::k_num_tract_params]) {
    pronunciation newProunciation;
    newProunciation.name = name;
    newProunciation.numOfVowels = numOfVowels;
    newProunciation.params = new float*[newProunciation.numOfVowels];
    for (int i = 0; i < newProunciation.numOfVowels; i++) {
        newProunciation.params[i] = new float[Tract::k_num_tract_params];
        for (int j = 0; j < Tract::k_num_tract_params; j++) {
            newProunciation.params[i][j] = params[i][j];
        }
    }
    newProunciation.duration = new float[numOfVowels];
    for (int i = 0; i < numOfVowels; i++) {
        newProunciation.duration[i] = durationInMs[i];
    }
    pronunciationLookUp[name] = newProunciation;
    availablePronunciations.push_back(name);
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

// add new pronounciation to sequencer
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

