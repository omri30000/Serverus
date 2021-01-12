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
    map<string,vector<RelativeIncStats>> _relIncStatsCollection; //lambda based vector, key is in format: "key1+key2"

    bool isStreamExists(string key) const;
    bool isRelStreamExists(string key) const;
    RelativeIncStats* getExistLink(RelativeIncStats& link);

public:
    IncStatsData();
    
    vector<IncStats>* registerStream(string uniqueKey) throw();
    vector<RelativeIncStats>* registerRelatedStreams(string firstUniqueKey, string secondUniqueKey) throw();

    void insertPacket(string key, Time timestamp) throw();
    void insertPacket(string key, float value, Time timestamp) throw();
    void insertPacket(string key, float value, Time timestamp, int lambdaIndex) throw();
    vector<float> getStatsOneDimension(string key) const throw();
    vector<float> getStatsTwoDimensions(string firstKey, string secondKey) const throw();
    void updateStatsTwoDimensions(string firstKey, Time timestamp, float value) const throw();
};