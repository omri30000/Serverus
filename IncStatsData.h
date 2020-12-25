#pragma once

#include "IncStats.h"
#include "Time.h"

#include <map>
#include <string>
#include <vector>

using std::vector;
using std::map;
using std::string;

class IncStatsData
{
protected:
    map<string,vector<IncStats>> _incStatsCollection;
    
public:
    IncStatsData();
    void registerStream(string uniqueKey);
    void insertPacket(string key, float value, Time timestamp, int lambdaindex);
    vector<float> getStats(string key);

}