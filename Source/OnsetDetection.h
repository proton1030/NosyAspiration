/*
  ==============================================================================

    OnsetDetection.h
    Created: 25 Apr 2018 5:05:45pm
    Author:  Hanyu Liu

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class OnsetDetection
{
    
public:
    OnsetDetection();
    ~OnsetDetection();
    void init(int blockLength, int sampleRate);
    void updateOnsetDetection(AudioSampleBuffer& buffer);
    
    bool bOnsetDetection;
    
private:
    const float m_fAlphaCoeff[2];
    const float m_fZCRThres;
    const float m_fRMSThres;
    const float m_fPpmDiffThres;
    const float m_iOnsetCooldownThres;
    
    int     m_iBlockLength;
    int     m_iSampleRate;
    
    float   m_fAlpha[2];
    
    
    float   m_fVPpmTemp;
    float   m_fCurrentBlockVPpm;
    float   m_fLastBlockVPpm;
    float   m_fCurrentBlockMAVPpm;
    float   m_fCurrentBlockZCR;
    float   m_fCurrentBlockRMS;
    
    bool    m_bOnsetTriggered;
    int     m_iOnsetCooldownCnt;
    
    void    calculatePpmAndZCR(const float* inputBuff);
};
