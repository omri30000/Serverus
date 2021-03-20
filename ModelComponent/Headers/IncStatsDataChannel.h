//
// Created by ofir on 31/12/2020.
//
#pragma once

#include "IncStatsData.h"
#include "Packet.h"

class IncStatsDataChannel : public IncStatsData
{

public:
    IncStatsDataChannel(TimeManager* timeManager);
    string getStreamKey(Packet pack);
    string getForeignKey(Packet pack);
};


