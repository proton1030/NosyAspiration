/*
  ==============================================================================

    Tract.h
    Created: 13 Mar 2018 3:01:06pm
    Author:  Hanyu Liu

  ==============================================================================
*/

#pragma once

#include <math.h>

class Tract
{
public:
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
                        lipOutput = 0,
                        noseOutput = 0,
                        velumTarget = 0.01,
                        reflectionLeft,
                        reflectionRight,
                        newReflectionLeft,
                        newReflectionRight;
    
    float               R[n], //component going right
                        L[n], //component going left
                        reflection[n+1],
                        newReflection[n+1],
                        junctionOutputR[n+1],
                        junctionOutputL[n+1],
                        maxAmplitude[n],
                        diameter[n],
                        restDiameter[n],
                        targetDiameter[n],
                        newDiameter[n],
                        A[n];
    
    //Nose Params
    static const int    noseLength = 28;
    int                 noseStart = n - noseLength + 1;
    float               reflectionNose,
                        newReflectionNose;
    float               noseR[noseLength],
                        noseL[noseLength],
                        noseJunctionOutputR[noseLength+1],
                        noseJunctionOutputL[noseLength+1],
                        noseReflection[noseLength+1],
                        noseDiameter[noseLength],
                        noseA[noseLength],
                        noseMaxAmplitude[noseLength];
    
    
    const int           m_iSampleRate;
    const int           m_iNumChannels;
    const int           m_iBlockLength;
    
    
    Tract(int sampleRate, int numChannels, int blockLength);
    virtual ~Tract();
    
    void reshapeTract();
    void updateReflections();
    void updateNoseReflections();
    void process(float glottalOutput, float lambda);
    void finishProcessingBlock();
private:
    float moveTowards(float current, float target, float amount);
    float moveTowards(float current, float target, float amountUp, float amountDown);
};
