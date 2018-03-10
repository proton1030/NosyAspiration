/*
  ==============================================================================

    WaveformGen.h
    Created: 10 Mar 2018 10:45:21am
    Author:  zhao yan

  ==============================================================================
*/

#pragma once
class WavefromGen {
public:
    WavefromGen(int sample_rate);
    void init();
    float runStep(float lambda);
    void setupWaveform(float lambda);
    float normalizedWaveform(float t);
    float getTimeInWaveForm();
    float getTotalTime();
    int   getWaveformLength();
    void  updateFreq(float new_frequency, float vibrato);
    void  updateTenseness(float new_tenseness);
private:
    float pre_frequency = 140;
    float cur_frequency = 140;
    float smooth_frequency = 140;
    float pre_tenseness = 0.6;
    float cur_tenseness = 0.6;
    float time_step;
    float time_in_waveform;
    float total_time;
    int   waveform_length;
    int   sample_rate = 44100;
    struct waveformParam {
        float Rd;
        float alpha;
        float E0;
        float epsilon;
        float shift;
        float delta;
        float Te;
        float omega;
    } waveformParam;
};
