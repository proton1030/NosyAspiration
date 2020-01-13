/*
  ==============================================================================

    PitchTrack.cpp
    Created: 23 Apr 2018 10:46:10pm
    Author:  zhao yan

  ==============================================================================
*/

#include "PitchTrack.h"
#include <cmath>
PitchTrack::PitchTrack():
block_size(0),
sample_rate(0),
fft_size(0),
fft_counter(0)
{

}

void PitchTrack::init(int block_size, int sample_rate, int fft_size)
{
    this->block_size = block_size;
    this->sample_rate = sample_rate;
    float order = ceil(log2(fft_size)) + 1;
    fft = std::make_unique<dsp::FFT>(order);
    this->fft_size = fft->getSize();
    fft_buff.reserve(fft_size * 2);
}

void PitchTrack::computeAcf()
{
    fft->performRealOnlyForwardTransform(&fft_buff[0]);
    for (int i = 0; i < fft_size * 2; i+=2)
    {
        // calculate conjugate element wise mulitply
        fft_buff[i] = fft_buff[i] * fft_buff[i] + fft_buff[i+1] * fft_buff[i+1];
        // seting imagine part to zero
        fft_buff[i+1] = 0;
    }
    fft->performRealOnlyInverseTransform(&fft_buff[0]);
}

std::vector<std::pair<int, float>> PitchTrack::getFundamentalFreq(float *inputBuff)
{
    std::vector<std::pair<int, float>> res;
    for (int i = 0; i < block_size; i++)
    {
        fft_buff[fft_counter] = delay_line->getPostInc();
        delay_line->putPostInc(inputBuff[i]);
        if (fft_counter == fft_size)
        {
            computeAcf();
            int start = 0;
            for (int i = 20; i < block_size; i++)
            {
                if (fft_buff[i] > fft_buff[i-10])
                {
                    start = i;
                    break;
                }
            }
            float lag = 0;
            float max_peak = 0;
            for (int i = start; i < block_size; i++)
            {
                if(fft_buff[i] > max_peak)
                {
                    max_peak = fft_buff[i];
                    lag = i;
                }
            }
            std::pair<int, float> pair {i, sample_rate / (lag - 1.0f)};
            res.push_back(pair);
        }
    }
    return res;
}
