/*
  ==============================================================================

    PitchTrack.cpp
    Created: 23 Apr 2018 10:46:10pm
    Author:  zhao yan

  ==============================================================================
*/

#include "PitchTrack.h"
#include <cmath>
PitchTrack::PitchTrack()
{

}

PitchTrack::~PitchTrack()
{
    delete [] m_acfBuff;
    delete [] m_fftBuff;
    m_fft->~FFT();
}


void PitchTrack::init(int blockLength, int sampleRate) {
    m_blockLength = blockLength;
    m_sampleRate = sampleRate;
    float order = ceil(log2(blockLength)) + 1;
    m_fft = new FFT(order);
    m_fftSize = m_fft->getSize();
    m_fftBuff = new float[m_fftSize * 2];
    m_acfBuff = new float[m_fftSize];
}

void PitchTrack::computeAcf(float *inputBuff) {
    memcpy(m_fftBuff, inputBuff, sizeof(float) * m_fftSize / 2);
    m_fft->performRealOnlyForwardTransform(m_fftBuff);
    for (int i = 0; i < m_fftSize * 2; i++) {
        m_fftBuff[i] = m_fftBuff[i] * m_fftBuff[i] * (1 - 2 * (i%2)); //calculating conjugate
    }
    m_fft->performRealOnlyInverseTransform(m_fftBuff);
    memcpy(m_acfBuff, m_fftBuff, sizeof(float) * m_fftSize);
}

float PitchTrack::getFundamentalFreq(float *inputBuff) {
    computeAcf(inputBuff);
    for (int i = 0; i < m_fftSize-1; i++) {
        m_acfBuff[i] = m_acfBuff[i+1] - m_acfBuff[i];
    }
    int t_init = 0;
    for (int i= 1; i < m_fftSize-1; i++) {
        if (m_acfBuff[i-1] >= 0 && m_acfBuff[i] < 0) {
            t_init = i;
            break;
        }
    }
    float f0 = m_sampleRate / (t_init - 1); // for beakpoint now
    
    return f0;
}
