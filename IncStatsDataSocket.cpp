//
// Created by ofir on 31/12/2020.
//

#include "IncStatsDataSocket.h"

string IncStatsDataSocket::getStreamKey(Packet pack) {
    return pack.getSourceIP() + std::to_string(pack.getSourcePort());
}
