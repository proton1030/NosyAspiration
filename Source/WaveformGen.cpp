/*
  ==============================================================================

    WaveformGen.cpp
    Created: 10 Mar 2018 11:20:37am
    Author:  zhao yan

  ==============================================================================
*/

#include "WaveformGen.h"
#include "SimplexNoise.h"
#include <math.h>


WavefromGen::WavefromGen(int sample_rate):
time_in_waveform(0)
{
    this->sample_rate = sample_rate;
    time_step = 1.0f / sample_rate;
}

void WavefromGen::init(){
    setupWaveform(0);
}

float WavefromGen::getTotalTime(){
    return total_time;
}

float WavefromGen::getTimeInWaveForm(){
    return time_in_waveform;
}

int WavefromGen::getWaveformLength(){
    return waveform_length;
}

void WavefromGen::updateFreq(float new_frequency, float vibrato = 0) {
    if (new_frequency > smooth_frequency) {
        smooth_frequency = fmin(smooth_frequency * 1.1, new_frequency);
    }
    if (new_frequency < smooth_frequency) {
        smooth_frequency = fmax(smooth_frequency / 1.1, new_frequency);
    }
    pre_frequency = cur_frequency;
    cur_frequency = smooth_frequency * (1 + vibrato);
}

void WavefromGen::updateTenseness(float new_tenseness) {
    pre_tenseness = cur_tenseness;
//    cur_tenseness = new_tenseness + 0.1 * SimplexNoise::simpleNoise1dWarper(total_time * 0.46) + 0.05 * SimplexNoise::simpleNoise1dWarper(total_time * 0.36);
    cur_tenseness = new_tenseness;
}

float WavefromGen::runStep(float lambda) {
    time_in_waveform += time_step;
    total_time += time_step;
    if (time_in_waveform > waveform_length) {
        time_in_waveform -= waveform_length;
        setupWaveform(lambda);
    }
    return normalizedWaveform(time_in_waveform/waveform_length);
}

void WavefromGen::setupWaveform(float lambda) {
    float interpolated_freq = pre_frequency*(1-lambda) + cur_frequency*lambda;
    float interpolated_tens = pre_tenseness*(1-lambda) + cur_tenseness*lambda;
    waveformParam.Rd = 3*(1-interpolated_tens);
    this->waveform_length = 1 / interpolated_freq;
    float Rd = waveformParam.Rd;
    if (waveformParam.Rd < 0.5) {
        Rd = 0.5;
    }
    if (waveformParam.Rd > 2.7) {
        Rd = 2.7;
    }
    float Ra = -0.01 + 0.048*Rd;
    float Rk = 0.224 + 0.118*Rd;
    float Rg = (Rk/4)*(0.5+1.2*Rk)/(0.11*Rd-Ra*(0.5+1.2*Rk));
    
    float Ta = Ra;
    float Tp = 1 / (2*Rg);
    float Te = Tp + Tp*Rk; //
    
    float epsilon = 1/Ta;
    float shift = exp(-epsilon * (1-Te));
    float Delta = 1 - shift;
    
    float RHSIntegral = (1/epsilon)*(shift - 1) + (1-Te)*shift;
    RHSIntegral = RHSIntegral/Delta;
    
    float totalLowerIntegral = - (Te-Tp)/2 + RHSIntegral;
    float totalUpperIntegral = -totalLowerIntegral;
    
    float omega = M_PI/Tp;
    float s = sin(omega*Te);
    
    float y = -M_PI*s*totalUpperIntegral / (Tp*2);
    float z = log(y);
    float alpha = z/(Tp/2 - Te);
    float E0 = -1 / (s*exp(alpha*Te));
    
    waveformParam.alpha = alpha;
    waveformParam.E0 = E0;
    waveformParam.epsilon = epsilon;
    waveformParam.shift = shift;
    waveformParam.delta = Delta;
    waveformParam.Te=Te;
    waveformParam.omega = omega;
}

float WavefromGen::normalizedWaveform (float t) {
    float output = 0;
    if (t>waveformParam.Te) output = (-exp(-waveformParam.epsilon * (t-waveformParam.Te)) + waveformParam.shift)/waveformParam.delta;
    else output = waveformParam.E0 * exp(waveformParam.alpha*t) * sin(waveformParam.omega * t);
    return output;
}
