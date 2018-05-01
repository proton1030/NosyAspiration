/*
  ==============================================================================

    PitchTrack.cpp
    Created: 23 Apr 2018 10:46:10pm
    Author:  zhao yan

  ==============================================================================
*/

#include "PitchTrack.h"
#include <cmath>
#include <iostream>
PitchTrack::PitchTrack():
m_fft(0),
m_blockLength(0),
m_sampleRate(0),
m_fftSize(0),
m_fftBuff(0),
m_acfBuff(0)
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
    m_acfBuff = new float[m_blockLength];
}

void PitchTrack::computeAcf(float *inputBuff) {
    memcpy(m_fftBuff, inputBuff, sizeof(float) * m_blockLength);
    m_fft->performRealOnlyForwardTransform(m_fftBuff);
    for (int i = 0; i < m_fftSize * 2; i+=2) {
        // calculate conjugate element wise mulitply
        m_fftBuff[i] = m_fftBuff[i] * m_fftBuff[i] + m_fftBuff[i+1] * m_fftBuff[i+1];
        // seting imagine part to zero
        m_fftBuff[i+1] = 0;
    }
    m_fft->performRealOnlyInverseTransform(m_fftBuff);
    memcpy(m_acfBuff, m_fftBuff, sizeof(float) * m_blockLength);
    memset(m_fftBuff, 0, sizeof(float) * m_fftSize * 2);
}

float PitchTrack::getFundamentalFreq(float *inputBuff) {
    computeAcf(inputBuff);
    int start = 0;
    for (int i = 20; i < m_blockLength; i++) {
        if (m_acfBuff[i] > m_acfBuff[i-10]) {
            start = i;
            break;
        }
    }
    float lag = 0;
    float max_peak = 0;
    for (int i= start; i < m_blockLength; i++) {
        if (m_acfBuff[i] > max_peak) {
            max_peak = m_acfBuff[i];
            lag = i;
        }
    }
    return m_sampleRate / (lag - 1.0f);
}
