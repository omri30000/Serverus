//
// Created by ofir on 31/12/2020.
//

#include "../Headers/IncStatsDataChannel.h"

/*
The function will generate the key that represents the stream
input: a packet
output: a key that represents the stream
*/
string IncStatsDataChannel::getStreamKey(Packet pack)
{
    return pack.getSourceIP() +'+' + pack.getDestIP();
}

/*
The function will generate the key of the destination entity in the conversation (to be used in 2D calculations)
input: a packet
output: a key that represents the stream
*/
string IncStatsDataChannel::getForeignKey(Packet pack)
{
    return pack.getDestIP()  + '+' + pack.getSourceIP();
}

IncStatsDataChannel::IncStatsDataChannel(TimeManager *timeManager) : IncStatsData(timeManager) {

}

