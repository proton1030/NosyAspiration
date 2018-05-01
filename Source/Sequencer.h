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
    void insert(string pronunciation, int pos);
    void Add(string pronunciation);
    void deleteNote(int pos);
    vector<string> getAvailablePronunciations();
    float* incPronunceAndGetVowel();
    float* incVowelAndGetVowel();
private:
    struct pronunciation {
        float** params;
        float*  duration;
        int     numOfVowels;
        string  name;
    };
    unordered_map<string, pronunciation> m_pronunciationLookUp;
    vector<pronunciation> m_curSequence;
    vector<string> m_availablePronunciations;
    int m_preIdx;
    int m_curPronunceationIdx;
    int m_curVowelIdx;
    float m_onsetTime;
    float m_timeStep;
    float m_sampleRate;
    float m_blockLength;
    void addPronunciation(string name, int numOfVowels, float* durationInMs,  float params[][Tract::k_num_tract_params]);
};
