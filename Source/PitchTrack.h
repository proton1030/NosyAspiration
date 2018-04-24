/*
  ==============================================================================

    PitchTrack.h
    Created: 23 Apr 2018 10:46:10pm
    Author:  zhao yan

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
using namespace dsp;
class PitchTrack
{
public:
    PitchTrack();
    ~PitchTrack();
    void init(int blockLength, int sampleRate);
    int getPitch(float* inputBuff);
private:
    FFT* m_fft;
    int m_blockLength;
    int m_sampleRate;
    int m_fftSize;
    float* m_fftBuff;
    float* m_acfBuff;
    void computeAcf(float* inputBuff);
};
