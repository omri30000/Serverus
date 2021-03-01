//
// Created by ofir on 01/03/2021.
//

#ifndef IDPS_20_21_MANIPULATOR_H
#define IDPS_20_21_MANIPULATOR_H


class Manipulator
{
protected:
    float levels[4];

public:
    int calcLevel(float anomalyScore);
    Manipulator(float maxThreshold);
};


#endif //IDPS_20_21_MANIPULATOR_H
