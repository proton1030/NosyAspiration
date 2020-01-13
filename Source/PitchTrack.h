/*
  ==============================================================================

    PitchTrack.h
    Created: 23 Apr 2018 10:46:10pm
    Author:  zhao yan

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "RingBuffer.h"
class PitchTrack
{
public:
    PitchTrack();
    void init(int block_size, int sample_rate, int fft_size);
    std::vector<std::pair<int, float>> getFundamentalFreq(float* inputBuff);
private:
    std::unique_ptr<dsp::FFT> fft;
    int block_size;
    float sample_rate; // declare samplerate as float to reduce implicit cast for calculating freq
    int fft_size;
    int fft_counter;
    
    std::unique_ptr<CRingBuffer<float>> delay_line;
    std::vector<float> fft_buff;
//    float* m_acfBuff;
    void computeAcf();
};
