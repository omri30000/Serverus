#pragma once

#include "IncStatsData.h"
#include "Packet.h"


#include <vector>
using std::vector;

class FeatureExtractor
{
protected:
    vector<float> _lambdas;
    
    IncStatsData _channelJitter;
    IncStatsData _channelSize;
    IncStatsData _socketSize;


public:
    //option for deafult values
    FeatureExtractor();
    FeatureExtractor(vector<float> lambdas);

    vector<float> extractNewFeaturesVector(Packet pack);
}