//
// Created by ofir on 31/12/2020.
//

#include "IncStatsDataChannel.h"

string IncStatsDataChannel::getStreamKey(Packet pack)
{
    return pack.getSourceIP();
}
