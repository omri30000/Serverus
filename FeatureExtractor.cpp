//
// Created by ofir on 30/12///

#include "FeatureExtractor.h"

//constructors
FeatureExtractor::FeatureExtractor() : FeatureExtractor(FeatureExtractor::DEFAULT_LAMBDAS)
{
}

FeatureExtractor::FeatureExtractor(vector<float> lambdas)
{
    this->_lambdas = lambdas;
}

vector<float> FeatureExtractor::extractNewFeaturesVector(Packet pack)
{
    //update
    this->_channelSize.insertPacket("key",pack.getLength(),pack.getArrivalTime());
    this->_channelJitter.insertPacket("key",0,pack.getArrivalTime());
    this->_socketSize.insertPacket("key",pack.getLength(),pack.getArrivalTime());

    vector<float> res;
    this->_channelSize.getStats("key");


}













