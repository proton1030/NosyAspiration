//
//  Glottis.h
//  NosyAspiration
//
//  Created by zhao yan on 2/18/18.
//

#ifndef Glottis_h
#define Glottis_h


#endif /* Glottis_h */
class Glottis {
public:
    Glottis(int sample_rate, int buffer_size, int frequency, float tenseness);
    ~Glottis();
    float runStep(float lambda, float noiseSource);
    
    
private:
    int sample_rate = 44100;
    int buffer_size = 1024;
    float tenseness = 0.6;
    
    struct wavformParam {
        float frequency;
        int   wavformlength;
        float Rd;
        float alpha;
        float E0;
        float epsilon;
        float shift;
        float delta;
        float Te;
        float omega;
    }
    
    float getNoiseModulator();
    float setupWaveform(float lambda, wavFormParam &wfp);
    float normalizeWaveform(float time);
    float finishBlock();
    
}
