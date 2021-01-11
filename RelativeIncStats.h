#pragma once

#include "IncStats.h"

#include <vector>
#include <string>

using std::vector;
using std::pair;
using std::string;

class RelativeIncStats
{
protected:
    IncStats* _firstIncStats;
    IncStats* _secondIncStats;

    float _firstCurrResidule;
    float _secondCurrResidule;

    float _sumResiduleProducts; //sum of residule products (A-uA)(B-uB)
    float _currWeight;
    Time _currTimeStamp; //last time stamp of the sum of residule products

    //stats
    float calcCovariance();
    float calcCorrelationCoefficiency();

public:
    RelativeIncStats(IncStats* first, IncStats* second);
    RelativeIncStats(IncStats* first, IncStats* second, Time initialTime);
    void update(string iSID, float newValue, Time timeStamp);
    void performDecay(Time timeStamp, int index);
};



