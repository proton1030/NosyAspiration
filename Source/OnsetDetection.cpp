/*
  ==============================================================================

    OnsetDetection.cpp
    Created: 25 Apr 2018 5:05:45pm
    Author:  Hanyu Liu

  ==============================================================================
*/

#include "OnsetDetection.h"
#include <math.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include <iostream>

OnsetDetection::OnsetDetection() : m_fAlphaCoeff{0.01 , 0.1}, m_fZCRThres(0.08), m_fRMSThres(0.002), m_fPpmDiffThres(0.0002), m_iOnsetCooldownThres(10)
{
    
}

OnsetDetection::~OnsetDetection()
{
    
}

void OnsetDetection::init(int blockLength, int sampleRate)
{
    m_iBlockLength = blockLength;
    m_iSampleRate = sampleRate;
    m_fCurrentBlockVPpm = 0.F;
    m_fLastBlockVPpm = 0.F;
    m_fCurrentBlockMAVPpm = 0.F;
    m_fCurrentBlockZCR = 0.F;
    m_fCurrentBlockRMS = 0.F;
    m_fVPpmTemp = 0.F;
    m_bOnsetTriggered = false;
    m_iOnsetCooldownCnt = 0;
    m_fAlpha[0] = 1.F - exp(-2.2F / (float(m_iSampleRate) * m_fAlphaCoeff[0]));
    m_fAlpha[1] = 1.F - exp(-2.2F / (float(m_iSampleRate) * m_fAlphaCoeff[1]));
    
    bOnsetDetection = 0;
}

void OnsetDetection::updateOnsetDetection(AudioSampleBuffer& buffer)
{
    // Set only read at channel number 1
    m_fCurrentBlockRMS = buffer.getRMSLevel(0, 0, m_iBlockLength);
    calculatePpmAndZCR(buffer.getReadPointer(0));
    m_fCurrentBlockMAVPpm = (m_fCurrentBlockVPpm + m_fLastBlockVPpm) / 2.F;
    m_fLastBlockVPpm = m_fCurrentBlockVPpm;
    
    if (m_fCurrentBlockZCR < m_fZCRThres && m_fCurrentBlockRMS > m_fRMSThres && m_fCurrentBlockVPpm - m_fCurrentBlockMAVPpm > m_fPpmDiffThres)
    {
        if (!m_bOnsetTriggered)
        {
            bOnsetDetection = 1;
            m_bOnsetTriggered = true;
            std::cout << "Onset" << std::endl;
        }
    }
    else
    {
        if (m_bOnsetTriggered)
        {
            if (m_iOnsetCooldownCnt < m_iOnsetCooldownThres)
                m_iOnsetCooldownCnt ++;
            else
            {
                m_iOnsetCooldownCnt = 0;
                m_bOnsetTriggered = false;
            }
        }
        bOnsetDetection = 0;
    }
//    std::cout << m_fCurrentBlockVPpm - m_fCurrentBlockMAVPpm << std::endl;
//    std::cout << (m_fCurrentBlockZCR < m_fZCRThres) << " " << (m_fCurrentBlockRMS > m_fRMSThres) << " " << (m_fCurrentBlockVPpm - m_fCurrentBlockMAVPpm > m_fPpmDiffThres) << std::endl;
    
    
}

void OnsetDetection::calculatePpmAndZCR(const float* inputBuff)
{
    float fMaxValue = 0.F;
    m_fCurrentBlockZCR = 0.F;
    for (int iSample = 0; iSample < m_iBlockLength; iSample++)
    {
        if ((iSample < m_iBlockLength - 1) && !signbit(inputBuff[iSample+1]) != !signbit(inputBuff[iSample]))
            m_fCurrentBlockZCR += 1.F;
        
        if (m_fVPpmTemp > abs(inputBuff[iSample]))
        {
            m_fVPpmTemp = (1 - m_fAlpha[1]) * m_fVPpmTemp;
        }
        else
        {
            m_fVPpmTemp = m_fAlpha[0] * abs(inputBuff[iSample]) + (1 - m_fAlpha[0]) * m_fVPpmTemp;
        }

        if (fMaxValue < m_fVPpmTemp)
        {
            fMaxValue = m_fVPpmTemp;
        }
    }
    m_fCurrentBlockZCR /= float(m_iBlockLength);
    m_fCurrentBlockVPpm = fMaxValue;
}

