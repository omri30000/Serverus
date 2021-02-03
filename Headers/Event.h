//
// Created by Omri Zaiman on 03/02/2021.
//

#pragma once
#include <string>
#include <vector>

#include "Time.h"

using byte = unsigned char;
using std::vector;
using std::string;

class Event {
protected:
    string _ipAddr;
    int _level;
    Time _date;

public:
    Event(string ip, int level, Time date);
    ~Event() = default;

    vector<byte> castToBinMessage();

};
