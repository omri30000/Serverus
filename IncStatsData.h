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
    bool isStreamExists(string key) const;

public:
    IncStatsData();
    void registerStream(string uniqueKey) throw();
    void insertPacket(string key, float value, Time timestamp) throw();
    void insertPacket(string key, float value, Time timestamp, int lambdaIndex) throw();
    vector<float> getStats(string key) const throw();



};