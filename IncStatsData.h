#pragma once

#include "IncStats.h"
#include "RelativeIncStats.h"
#include "Time.h"

#include <map>
#include <string>
#include <vector>
#include <utility>

using std::vector;
using std::map;
using std::string;
using std::pair;

class IncStatsData
{
protected:
    map<string,vector<IncStats>> _incStatsCollection;
    vector<RelativeIncStats> _relIncStatsCollection; //Relative Inc Stats

    bool isStreamExists(string key) const;
    RelativeIncStats* getExistLink(RelativeIncStats& link);

public:
    IncStatsData();
    
    vector<IncStats>* registerStream(string uniqueKey) throw();
    vector<RelativeIncStats>* registerRelatedStreams(string firstUniqueKey, string secondUniqueKey) throw();

    void insertPacket(string key, Time timestamp) throw();
    void insertPacket(string key, float value, Time timestamp) throw();
    void insertPacket(string key, float value, Time timestamp, int lambdaIndex) throw();
    vector<float> getStats(string key) const throw();
};