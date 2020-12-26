#pragma once

#include "Time.h"


class IncStats
{
protected:
    int _instanceNumber;
    float _weight;
    float _linearSum;
    float _squareSum;
    Time _timeStamp;
    float _decayFactor;
    float _variance;
    float _standardDeviation;

    void performDecay(Time timeStamp);
    float calcMean();
    float calcVariance();
    float calcStandardDeviation();

public:
    IncStats(float decayFactor);
    void insertElement(float element, Time timeStemp);

};


