//
// Created by ofir on 30/12///

#include "FeatureExtractor.h"


const vector<float> FeatureExtractor::DEFAULT_LAMBDAS= {0.01,0.1,1,3,5};
//constructors
FeatureExtractor::FeatureExtractor() : FeatureExtractor(FeatureExtractor::DEFAULT_LAMBDAS)
{
}

FeatureExtractor::FeatureExtractor(vector<float> lambdas)
{
    this->_lambdas = lambdas;
}

/*
This function extracts the vector stats for a specific packet
Input: pack - the packet to add :Packet
Output: The statistics vector :Vector<float>
*/
vector<float> FeatureExtractor::extractNewFeaturesVector(Packet pack) {
    //update
    string channelKey = this->_channelSize.getStreamKey(pack);
    string socketKey = this->_socketSize.getStreamKey(pack);

    this->_channelSize.insertPacket(channelKey, pack.getLength(), pack.getArrivalTime());
    this->_channelJitter.insertPacket(channelKey,  pack.getArrivalTime());
    this->_socketSize.insertPacket(socketKey, pack.getLength(), pack.getArrivalTime());

    vector<float> res;
    vector<float> tmp;

    tmp = this->_channelSize.getStats(channelKey);
    res.insert(res.begin(), tmp.begin(), tmp.end());

    tmp = this->_channelJitter.getStats(channelKey);
    res.insert(res.begin(), tmp.begin(), tmp.end());

    tmp = this->_socketSize.getStats(socketKey);
    res.insert(res.begin(), tmp.begin(), tmp.end());

    return res;

}