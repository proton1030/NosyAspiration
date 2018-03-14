/*
  ==============================================================================

    Glottis.h
    Created: 10 Mar 2018 3:25:27pm
    Author:  zhao yan

  ==============================================================================
*/

#pragma once

#include "WaveformGen.h"
#include <iostream>

class Glottis
{
public:
    enum GlottisParams {
        k_intensity,
        k_tenseness,
        k_frequency,
        k_vibrato_amount,
        k_vibrato_freq,
        k_num_params
    };
    
    Glottis(int sample_rate, int num_channels);
    ~Glottis();
    void setParam(GlottisParams paramType, float paramVal);
    float getParam(GlottisParams paramType);
    float runStep(float lambda, float noise_source);
    void process(float **input_buffer, float **output_buffer, int num_samples);
    void process(float *input_buffer, float *output_buffer, int num_samples);
private:
    int sample_rate;
    int num_channels;
    float params[k_num_params];
    WavefromGen* waveform_gen;
    
    float getNoiseModulator();
    void finishBlock();
};
