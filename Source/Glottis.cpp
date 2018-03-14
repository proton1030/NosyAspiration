/*
  ==============================================================================

    Glottis.cpp
    Created: 10 Mar 2018 3:25:20pm
    Author:  zhao yan

  ==============================================================================
*/

#include "Glottis.h"
#include "SimplexNoise.h"
#include <math.h>

Glottis::Glottis(int sample_rate, int num_channels):
sample_rate(sample_rate),
num_channels(num_channels)
{
    waveform_gen = new WavefromGen(sample_rate);
    waveform_gen->init();
    setParam(k_intensity, 1);
    setParam(k_frequency, 140);
    setParam(k_tenseness, 0.6);
    setParam(k_vibrato_freq, 6);
    setParam(k_vibrato_amount, 0.005);
}

Glottis::~Glottis(){
    delete waveform_gen;
}

void Glottis::setParam(Glottis::GlottisParams paramType, float paramVal) {
    params[paramType] = paramVal;
}

float Glottis::getParam(Glottis::GlottisParams paramType) {
    return params[paramType];
}

float Glottis::getNoiseModulator() {
    float voiced = 0.1 + 0.2 * fmax(0, sin(M_PI * 2 * waveform_gen->getTimeInWaveForm()/waveform_gen->getWaveformLength()));
    return params[k_tenseness] * params[k_intensity] * voiced + (1- params[k_tenseness] * params[k_intensity]) * 0.3;
}

float Glottis::runStep(float lambda, float noise_source) {
    float wave_form_out = waveform_gen->runStep(lambda);
    float aspiration = params[k_intensity] * (1-sqrt(params[k_tenseness])) * getNoiseModulator() * noise_source;
    aspiration *= 0.2 + 0.02* SimplexNoise::simpleNoise1dWarper(waveform_gen->getTotalTime() * 1.99);
    wave_form_out += aspiration;
//    std::cout << wave_form_out << std::endl;
    return wave_form_out;
}

void Glottis::process(float **input_buffer, float **output_buffer, int num_samples) {
    for (int i = 0; i < num_channels; i++) {
        for (int j = 0; j < num_samples; j++) {
            float lambda = j / num_samples;
            output_buffer[i][j] = runStep(lambda, input_buffer[i][j]);
        }
    }
    finishBlock();
}

void Glottis::process(float *input_buffer, float *output_buffer, int num_samples) {
    for (int i = 0; i < num_samples; i++) {
        float lambda = (float)i / num_samples;
        output_buffer[i] = runStep(lambda, 0);
//        std::cout << output_buffer[i] << std::endl;
    }
    finishBlock();
}

void Glottis::finishBlock() {
    float vibrato = 0;
    vibrato += params[k_vibrato_amount] * sin(2*M_PI * waveform_gen->getTotalTime() * params[k_vibrato_freq]);
    vibrato += 0.02 * SimplexNoise::simpleNoise1dWarper(waveform_gen->getTotalTime() * 4.07);
    vibrato += 0.04 * SimplexNoise::simpleNoise1dWarper(waveform_gen->getTotalTime() * 2.15);
    waveform_gen->updateFreq(params[k_frequency], vibrato);
    waveform_gen->updateTenseness(params[k_tenseness]);
}
