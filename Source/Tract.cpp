/*
  ==============================================================================

    Tract.cpp
    Created: 13 Mar 2018 3:01:06pm
    Author:  Hanyu Liu

  ==============================================================================
*/

#include "Tract.h"
#include <algorithm>

Tract::Tract(int sampleRate, int numChannels, int blockLength):
m_iSampleRate(sampleRate),
m_iNumChannels(numChannels),
m_iBlockLength(blockLength)
{
    for (int i=0; i<n; i++)
    {
        float fDiameterParam = 0;
        if (i < 7*n/44-0.5)
            fDiameterParam = 0.6;
        else if (i < 12*n/44)
            fDiameterParam = 1.1;
        else
            fDiameterParam = 1.5;
        diameter[i] = restDiameter[i] = targetDiameter[i] = newDiameter[i] = fDiameterParam;
    }
    
    for (int i = 0; i < noseLength; i++)
    {
        float fDiameterParam;
        float d = 2.F * (i / noseLength);
        if (d < 1.F)
            fDiameterParam = 0.4F + 1.6F * d;
        else
            fDiameterParam = 0.5F + 1.5F * (2.F - d);
        fDiameterParam = fmin(fDiameterParam, 1.9);
        noseDiameter[i] = fDiameterParam;
    }
    newReflectionLeft = 0.F;
    newReflectionRight = 0.F;
    newReflectionNose = 0.F;
    updateReflections();
    updateNoseReflections();
    noseDiameter[0] = velumTarget;
    deltaTime = float(blockLength) / float(sampleRate);
}

Tract::~Tract()
{
    
}

void Tract::reshapeTract()
{
    float amount = deltaTime * movementSpeed; ;
    int newLastObstruction = -1;
    for (int i = 0; i < n; i++)
    {
        if (diameter[i] <= 0)
            newLastObstruction = i;
        float slowReturn;
        if (i < noseStart)
            slowReturn = 0.6F;
        else if (i >= tipStart)
            slowReturn = 1.F;
        else
            slowReturn = 0.6F + 0.4F * float(i - noseStart)/float(tipStart - noseStart);
        diameter[i] = moveTowards(diameter[i], targetDiameter[i], slowReturn*amount, 2*amount);
    }
//    if (lastObstruction > -1 && newLastObstruction == -1 && noseA[0] < 0.05)
//    {
//        addTransient(lastObstruction);
//    }
    lastObstruction = newLastObstruction;
    
    amount = deltaTime * movementSpeed;
    noseDiameter[0] = moveTowards(noseDiameter[0], velumTarget, amount*0.25, amount*0.1);
    noseA[0] = noseDiameter[0] * noseDiameter[0];
    
}

void Tract::updateReflections()
{
    for (int i=0; i<n; i++)
    {
        A[i] = diameter[i] * diameter[i]; //ignoring PI etc.
    }
    for (int i=1; i<n; i++)
    {
        reflection[i] = newReflection[i];
        if (A[i] == 0)
            newReflection[i] = 0.999; //to prevent some bad behaviour if 0
        else
            newReflection[i] = (A[i-1] - A[i]) / (A[i-1] + A[i]);
    }
    
    //now at junction with nose
    reflectionLeft = newReflectionLeft;
    reflectionRight = newReflectionRight;
    reflectionNose = newReflectionNose;
    float sum = A[noseStart] + A[noseStart+1] + noseA[0];
    newReflectionLeft = (2 * A[noseStart] - sum) / sum;
    newReflectionRight = (2 * A[noseStart + 1] - sum) / sum;
    newReflectionNose = (2 * noseA[0] - sum) / sum;
}

void Tract::updateNoseReflections()
{
    for (int i=0; i<noseLength; i++)
    {
        noseA[i] = noseDiameter[i] * noseDiameter[i];
    }
    for (int i=1; i<noseLength; i++)
    {
        noseReflection[i] = (noseA[i-1] - noseA[i]) / (noseA[i-1] + noseA[i]);
    }
}

void Tract::process(float glottalOutput, float lambda)
{
    float updateAmplitudes = (float(rand()) / float(RAND_MAX)) < 0.1;
    
    //mouth
    // processTransients();
    // addTurbulenceNoise(turbulenceNoise);
    
    //glottalReflection = -0.8 + 1.6 * Glottis.newTenseness;
    junctionOutputR[0] = L[0] * glottalReflection + glottalOutput;
    junctionOutputL[n] = R[n-1] * lipReflection;
    
    for (int i = 1; i < n; i++)
    {
        float r = reflection[i] * (1-lambda) + newReflection[i]*lambda;
        float w = r * (R[i-1] + L[i]);
        junctionOutputR[i] = R[i-1] - w;
        junctionOutputL[i] = L[i] + w;
    }
    
    //now at junction with nose
    float r = newReflectionLeft * (1-lambda) + reflectionLeft * lambda;
    junctionOutputL[noseStart] = r * R[noseStart-1] + (1 + r) * (noseL[0] + L[noseStart]);
    r = newReflectionRight * (1-lambda) + reflectionRight * lambda;
    junctionOutputR[noseStart] = r * L[noseStart] + (1+r) * (R[noseStart-1] + noseL[0]);
    r = newReflectionNose * (1-lambda) + reflectionNose * lambda;
    noseJunctionOutputR[0] = r * noseL[0] + (1+r) * (L[noseStart]+R[noseStart-1]);
    
    for (int i=0; i<n; i++)
    {
        R[i] = junctionOutputR[i] * 0.999;
        L[i] = junctionOutputL[i+1] * 0.999;
        //R[i] = Math.clamp(junctionOutputR[i] * fade, -1, 1);
        //L[i] = Math.clamp(junctionOutputL[i+1] * fade, -1, 1);
        if (updateAmplitudes)
        {
            float amplitude = abs(R[i]+L[i]);
            if (amplitude > maxAmplitude[i])
                maxAmplitude[i] = amplitude;
            else maxAmplitude[i] *= 0.999;
        }
    }
    lipOutput = R[n-1];
    
    //nose
    noseJunctionOutputL[noseLength] = noseR[noseLength-1] * lipReflection;
    for (int i=1; i<noseLength; i++)
    {
        float w = noseReflection[i] * (noseR[i-1] + noseL[i]);
        noseJunctionOutputR[i] = noseR[i-1] - w;
        noseJunctionOutputL[i] = noseL[i] + w;
    }
    
    for (int i=0; i<noseLength; i++)
    {
        noseR[i] = noseJunctionOutputR[i] * fade;
        noseL[i] = noseJunctionOutputL[i+1] * fade;
        //noseR[i] = Math.clamp(noseJunctionOutputR[i] * fade, -1, 1);
        //noseL[i] = Math.clamp(noseJunctionOutputL[i+1] * fade, -1, 1);
        if (updateAmplitudes)
        {
            float amplitude = abs(noseR[i] + noseL[i]);
            if (amplitude > noseMaxAmplitude[i])
                noseMaxAmplitude[i] = amplitude;
            else
                noseMaxAmplitude[i] *= 0.999;
        }
    }
    noseOutput = noseR[noseLength-1];
}

void Tract::finishProcessingBlock()
{
    reshapeTract();
    updateReflections();
}

float Tract::moveTowards(float current, float target, float amount)
{
    if (current < target)
        return fmin(current + amount, target);
    else
        return fmax(current - amount, target);
}

float Tract::moveTowards(float current, float target, float amountUp, float amountDown)
{
    if (current < target)
        return fmin(current + amountUp, target);
    else
        return fmax(current - amountDown, target);
}
