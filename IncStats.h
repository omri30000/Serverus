#pragma once

#include "Time.h"

#include <vector>

using std::vector;


class IncStats
{
protected:
    int _instanceNumber;
    float _weight;
    float _linearSum;
    float _squaredSum;
    Time _timeStamp;
    float _decayFactor;
    float _mean;
    float _standardDeviation;

    void performDecay(Time timeStamp);

    //1D stats
    float calcMean();
    float calcStandardDeviation();

    //2D stats
    float calcMagnitude(IncStats other);
    float calcRadius(IncStats other);

public:
    IncStats(float decayFactor);
    void insertElement(Time timeStamp);
    void insertElement(float element, Time timeStamp);
    vector<float> getStats() const;

};


