#pragma once

#include "IncStatsData.h"
#include "Packet.h"
#include "IncStatsDataChannel.h"
#include "IncStatsDataSocket.h"


#include <vector>
using std::vector;

class FeatureExtractor
{
protected:
    static const vector<float> DEFAULT_LAMBDAS;

    vector<float> _lambdas;
    
    IncStatsDataChannel _channelJitter;
    IncStatsDataChannel _channelSize;
    IncStatsDataSocket _socketSize;


public:
    //option for deafult values
    FeatureExtractor();
    FeatureExtractor(vector<float> lambdas);

    vector<float> extractNewFeaturesVector(Packet pack);
};

const vector<float> FeatureExtractor::DEFAULT_LAMBDAS= {0.01,0.1,1,3,5};