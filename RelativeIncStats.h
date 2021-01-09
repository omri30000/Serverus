#pragma once

#include "IncStats.h"

#include <vector>
#include <pair>

using std::vector;
using std::pair;

class RelativeIncStats
{
protected:
    IncStats* _firstIncStats;
    IncStats* _secondIncStats;

    float _sumResiduleProducts; //sum of residule products (A-uA)(B-uB)
    float _currWeight;

    
    //void performDecay(Time timeStamp);

    //stats
    float calcCovariance();
    float calcCorrelationCoefficiency();

public:
    RelativeIncStats(IncStats* first, IncStats* second);

};



