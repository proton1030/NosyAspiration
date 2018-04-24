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
//    fft = new dsp::FFT(3);
}
void PitchTrack::init(int blockLength, int sampleRate) {
    m_blockLength = blockLength;
    m_sampleRate = sampleRate;
    float order = ceil(log2(blockLength)) + 1;
    m_fft = new FFT(order);
    m_fftSize = m_fft->getSize();
    m_fftBuff = new float[m_fftSize];
    m_acfBuff = new float[m_fftSize/2];
}
void PitchTrack::computeAcf(float *inputBuff) {
    memcpy(m_fftBuff, inputBuff, sizeof(float) * m_fftSize / 2);
    m_fft->performRealOnlyForwardTransform(m_fftBuff);
    for (int i = 0; i < m_fftSize; i++) {
        inputBuff[i] = - inputBuff[i] * inputBuff[i];
    }
    m_fft->performRealOnlyInverseTransform(m_fftBuff);
    memcpy(m_acfBuff, m_fftBuff, sizeof(float) * m_fftSize / 2);
}
int PitchTrack::getPitch(float *inputBuff) {
    computeAcf(inputBuff);
    
    return 0;
}
