//
// Created by ofir on 31/12/2020.
//

#pragma once

#include "IncStatsData.h"
#include "Packet.h"
#include "TimeManager.h"

class IncStatsDataSocket : public IncStatsData{

public:
    IncStatsDataSocket(TimeManager* timeManager);
    string getStreamKey(Packet pack);
    string getForeignKey(Packet pack);
};


