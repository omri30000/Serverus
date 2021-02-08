//
// Created by ofir on 31/12/2020.
//

#include "../Headers/IncStatsDataSocket.h"

/*
The function will generate the key that represents the stream
input: a packet
output: a key that represents the stream
*/
string IncStatsDataSocket::getStreamKey(Packet pack) {
    return pack.getSourceIP() + ":"+std::to_string(pack.getSourcePort()) + '+' +pack.getDestIP() + ':' + std::to_string(pack.getDestPort());
}

/*
The function will generate the key of the destination entity in the conversation (to be used in 2D calculations)
input: a packet
output: a key that represents the stream
*/
string IncStatsDataSocket::getForeignKey(Packet pack)
{
    return  pack.getDestIP() + ':' + std::to_string(pack.getDestPort()) +'+'+ pack.getSourceIP() + ":"+std::to_string(pack.getSourcePort());
}
