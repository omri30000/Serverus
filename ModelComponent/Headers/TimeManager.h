//
// Created by ofir on 10/03/2021.
//

#ifndef IDPS_20_21_TIMEMANAGER_H
#define IDPS_20_21_TIMEMANAGER_H

#include "Time.h"

class TimeManager
{
protected:
    Time _lastSeen;
    bool _state;

public:
    TimeManager(bool state);

    void updateTime(Time newTime);

    Time getLastTime();

};


#endif //IDPS_20_21_TIMEMANAGER_H
