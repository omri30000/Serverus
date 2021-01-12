//
// Created by ofir on 31/12/2020.
//

#pragma once

#include "IncStatsData.h"
#include "Packet.h"

class IncStatsDataSocket : public IncStatsData{

public:
    string getStreamKey(Packet pack);
    string getForeignKey(Packet pack);
};


