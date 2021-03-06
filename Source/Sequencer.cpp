/*
  ==============================================================================

    Sequencer.cpp
    Created: 28 Apr 2018 9:06:37am
    Author:  zhao yan

  ==============================================================================
*/

#include "Sequencer.h"
Sequencer::Sequencer():
m_preIdx(0),
m_curPronunceationIdx(0),
m_curVowelIdx(0),
m_sampleRate(0),
m_blockLength(0)
{
    
}
Sequencer::~Sequencer()
{
    for (vector<pronunciation>::iterator it = m_curSequence.begin(); it != m_curSequence.end(); it++) {
        for (int i = 0; i < it->numOfVowels; i++) {
            delete [] it->params[i];
        }
        delete [] it->params;
        delete [] it->duration;
    }
}

//adding in prounciation params
void Sequencer::init(float sampleRate, float blockLength) {
    m_sampleRate = sampleRate;
    m_blockLength = blockLength;
    m_timeStep = m_blockLength/m_sampleRate * 1000;
    
    float ya_params[2][Tract::k_num_tract_params] =
    {
        {13.58, 2.9, 40.45, 0.88},
        {13.58, 2.9, 40.45, 2.33}
    };
    float ya_duration[2] = {80.0f, -1};
    addPronunciation("ya", 2, ya_duration, ya_params);
    
    float ei_params[2][Tract::k_num_tract_params] =
    {
        {7.8, 2.61, 40.45, 0.51},
        {31.98, 2.52, 42, 2.5}
    };
    float ei_duration[2] = {80.0f, -1};
    addPronunciation("ei", 2, ei_duration, ei_params);

    
    float ri_params[2][Tract::k_num_tract_params] =
    {
        {28.91, 2.43, 16.44, 0.48},
        {28.91, 2.43, 16.44, 0.48}
    };
    float ri_duration[2] = {100.0f, -1};
    addPronunciation("ri", 2, ri_duration, ri_params);
}

void Sequencer::reset() {
    m_pronunciationLookUp.clear();
    m_availablePronunciations.clear();
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
    m_pronunciationLookUp[name] = newProunciation;
    m_availablePronunciations.push_back(name);
}

float* Sequencer::incPronunceAndGetVowel() {
    if (m_curSequence.size() > 0){
        m_preIdx = m_curPronunceationIdx;
        m_curPronunceationIdx = (m_curPronunceationIdx + 1) % m_curSequence.size();
        m_curVowelIdx = 0;
        m_onsetTime = 0;
//        std::cout << m_curSequence[m_preIdx].name << std::endl;
        return m_curSequence[m_preIdx].params[0];
    } else {
        return 0;
    }
}

float* Sequencer::incVowelAndGetVowel() {
    if (m_curSequence.size() > 0) {
        m_onsetTime += m_timeStep;
        if (m_onsetTime >= m_curSequence[m_preIdx].duration[m_curVowelIdx] && m_curSequence[m_preIdx].duration[m_curVowelIdx] > 0) {
            m_curVowelIdx++;
        }
        return m_curSequence[m_preIdx].params[m_curVowelIdx];
    } else {
        return 0;
    }
}

// add new pronounciation to sequencer
void Sequencer::Add(string pronouciation) {
    m_curSequence.push_back(m_pronunciationLookUp[pronouciation]);
    m_curPronunceationIdx = 0;
}

// pos is zero based
void Sequencer::insert(string pronounciation, int pos) {
    m_curSequence.insert(m_curSequence.begin() + pos, m_pronunciationLookUp[pronounciation]);
    m_curPronunceationIdx = 0;

    
}

// pos is zero based
void Sequencer::deleteNote(int pos) {
    m_curSequence.erase(m_curSequence.begin() + pos);
    m_curPronunceationIdx = 0;
}

vector<string> Sequencer::getAvailablePronunciations(){
    return m_availablePronunciations;
}

vector<string> Sequencer::getCurrentPronunciations(){
    vector<string> currentSequence;
    for (int i = 0; i < int(m_curSequence.size()); i++)
        currentSequence.push_back(m_curSequence[i].name);
    return currentSequence;
}

int Sequencer::getCurrentPronounciationIdx(){
    return m_preIdx;
}

