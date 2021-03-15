//
// Created by ofir on 01/03/2021.
//

#include "../Headers/Manipulator.h"

Manipulator::Manipulator(float maxThreshold)
{
    //levels[0] = maxThreshold;
    levels[0] = maxThreshold*1.15;
    levels[1] = maxThreshold*1.5;
    levels[2] = maxThreshold*2;
    levels[3] = maxThreshold*3;
}

int Manipulator::calcLevel(float anomalyScore)
{
    int level = 0;
    while(level < 4 && anomalyScore >levels[level] )
    {
        level++;
    }
    return level;
}


