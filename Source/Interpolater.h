/*
  ==============================================================================

    Interpolater.h
    Created: 29 Oct 2019 10:14:28pm
    Author:  zhao yan

  ==============================================================================
*/

#pragma once
#include <vector>
class Interpolater
{
public:
    template<class T>
    static T linearInterpolate(const std::vector<T> &vec, float read_pos)
    {
        int rpi = static_cast<int>(std::floor(read_pos));
        float frac = read_pos - rpi;
        return (1 - frac) * vec[rpi % vec.size()] + frac * vec[(rpi + 1) % vec.size()];
    }
};
