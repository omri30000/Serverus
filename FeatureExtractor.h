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
    ~FeatureExtractor() = default;
    FeatureExtractor(vector<float> lambdas);

    vector<float> extractNewFeaturesVector(Packet pack);
};

