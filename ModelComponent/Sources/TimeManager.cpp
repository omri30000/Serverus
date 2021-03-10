//
// Created by ofir on 10/03/2021.
//

#include "../Headers/TimeManager.h"

TimeManager::TimeManager(bool state)
{
    _state = state;
}


void TimeManager::updateTime(Time newTime)
{
    _lastSeen = newDate;
}
/*
 This function returns the last seen time, if forensics
    otherwise(if on real-time) the time now
    Input:Now
    Output:the last seen time
 */
Time TimeManager::getLastTime() {
    if(_state)// if forensics
        return _lastSeen;

    return Time(1);//return now Date
}
