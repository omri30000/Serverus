#pragma once

#include "../Headers/IncStats.h"
#include "../Headers/RelativeIncStats.h"
#include "../Headers/Time.h"
#include "../Headers/TimeManager.h"

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <mutex>
#include <thread>

using std::vector;
using std::map;
using std::string;
using std::pair;
using std::mutex;
using std::lock_guard;

class IncStatsData
{
protected:
    map<string,vector<IncStats*>> _incStatsCollection;

    map<string,vector<RelativeIncStats*>> _relIncStatsCollection; //lambda based vector, key is in format: "key1+key2"/2
    mutex _incStatsCollectionLock;

    bool _isRunning;
    std::thread _cleaningThread;

    TimeManager* _timeManager;
    bool isStreamExists(string key) const;
    bool isRelStreamExists(string key) const;
    void cleanInactiveStats(float limit);
    string getCombinedKey(string first, string second) const;
    void deleteStream(string key);
    void deleteStream2D(string key);

public:
    IncStatsData(TimeManager* timeManager);
    ~IncStatsData();
    vector<IncStats*> registerStream(string uniqueKey) throw();
    vector<RelativeIncStats*> registerRelatedStreams(string key, Time timestamp) throw();

    void insertPacket(string key, Time timestamp) throw();

    void insertPacket(string key, float value, Time timestamp) throw();

    void insertPacket(string key, float value, Time timestamp, int lambdaIndex) throw();

    vector<float> getStatsOneDimension(string key) throw();
    vector<float> getStatsTwoDimensions(string key) throw();
    string getCombinedKey(string key) const;

    void removeStream(string pack); //for outer use only

};