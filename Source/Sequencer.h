/*
  ==============================================================================

    Sequencer.h
    Created: 28 Apr 2018 9:06:45am
    Author:  zhao yan

  ==============================================================================
*/

#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "Tract.h"
using namespace std;
class Sequencer
{
public:
    Sequencer(float sampleRate, float blockLength);
    ~Sequencer();
    void init();
    void insert(string element, int pos);
    void Add(string element);
    void deleteNote(int pos);
    vector<string> getAvailableElements();
    float* incPronunceAndGetVowel();
    float* incVowelAndGetVowel();
private:
    struct pronunciation {
        float** params;
        float*  duration;
        int     numOfVowels;
        string  name;
    };
    unordered_map<string, pronunciation> pronunciationLookUp;
    vector<pronunciation> curSequence;
    vector<string> availableElements;
    pronunciation* curPronounciation;
    int curPronunceationIdx;
    int curVowelIdx;
    float onsetTime;
    float timeStep;
    float sampleRate;
    float blockLength;
};
