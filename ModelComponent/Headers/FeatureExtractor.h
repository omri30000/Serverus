#pragma once

#include "IncStatsData.h"
#include "Packet.h"
#include "IncStatsDataChannel.h"
#include "IncStatsDataSocket.h"
#include "TimeManager.h"


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
    FeatureExtractor(TimeManager* timeManager);

    ~FeatureExtractor() = default;
    FeatureExtractor(vector<float> lambdas,TimeManager* timeManager);

    vector<float> extractNewFeaturesVector(Packet pack);
};

