/*
  ==============================================================================

    Tract.h
    Created: 13 Mar 2018 3:01:06pm
    Author:  Hanyu Liu

  ==============================================================================
*/

#pragma once

#include <math.h>
#include <vector>

class Tract
{
public:
    enum TractParams {
        k_tongueBaseIndex,
        k_tongueBaseDiameter,
        
        k_num_tract_params
    };
    
    Tract(int sampleRate, int numChannels, int blockLength);
    virtual ~Tract();
    void setParam(TractParams paramType, float paramVal);
    float getParam(TractParams paramType);
    void process(float *input_buffer, float *output_buffer, int num_samples);
    
private:
    const int           m_iSampleRate;
    const int           m_iNumChannels;
    const int           m_iBlockLength;
    
    static const int    n = 44;
    int                 bladeStart = floor(10.F * n / 44.F);
    int                 tipStart = floor(32.F * n / 44.F);
    int                 lipStart = floor(39.F * n / 44.F);
    float               deltaTime;
    
    //Tract Params
    float               glottalReflection = 0.75F,
                        lipReflection = -0.85F,
                        lastObstruction = -1.F,
                        fade = 1.0F, //0.9999,
                        movementSpeed = 15.F, //cm per second
                        lipOutput = 0.0F,
                        noseOutput = 0.0F,
                        velumTarget = 0.01F,
                        reflectionLeft = 0.0F,
                        reflectionRight = 0.0F,
                        newReflectionLeft = 0.0F,
                        newReflectionRight = 0.0F;
    
    float               R[n] = {0.F}, //component going right
                        L[n] = {0.F}, //component going left
                        reflection[n+1] = {0.F},
                        newReflection[n+1] = {0.F},
                        junctionOutputR[n+1] = {0.F},
                        junctionOutputL[n+1] = {0.F},
                        maxAmplitude[n] = {0.F},
                        diameter[n] = {0.F},
                        restDiameter[n] = {0.F},
                        targetDiameter[n] = {0.F},
                        newDiameter[n] = {0.F},
                        A[n] = {0.F};
    
    //Nose Params
    static const int    noseLength = 28;
    int                 noseStart = n - noseLength + 1;
    float               reflectionNose = 0.0F,
                        newReflectionNose = 0.0F;
    float               noseR[noseLength] = {0.F},
                        noseL[noseLength] = {0.F},
                        noseJunctionOutputR[noseLength+1] = {0.F},
                        noseJunctionOutputL[noseLength+1] = {0.F},
                        noseReflection[noseLength+1] = {0.F},
                        noseDiameter[noseLength] = {0.F},
                        noseA[noseLength] = {0.F},
                        noseMaxAmplitude[noseLength] = {0.F};

    struct trans {
        int     position;
        float   timeAlive,
                lifeTime,
                strength,
                exponent;
    };
    std::vector<trans>  transients;
    
    void reshapeTract();
    void updateReflections();
    void updateNoseReflections();
    float runStep(float glottalOutput, float lambda);
    void  finishProcessingBlock();
    void  setRestDiameter();
    void  addTransient(int position);
    void  processTransients();
    
    //helper functions
    float moveTowards(float current, float target, float amount);
    float moveTowards(float current, float target, float amountUp, float amountDown);
    float clamp(float number, float min, float max);
    
    float params[k_num_tract_params];
};
