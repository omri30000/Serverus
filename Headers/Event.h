//
// Created by Omri Zaiman on 03/02/2021.
//

#pragma once
#include <string>
#include <vector>
#include <cmath>

#include "Time.h"

using byte = unsigned char;
using std::vector;
using std::string;

class Event {
protected:
    string _ipAddr;
    int _level;
    Time _date;

    int calcDateMilliseconds() const;

public:
    Event(string ip, int level, Time date);
    ~Event() = default;

    vector<byte> castToBinMessage() const throw();
    vector<byte> castIpToBin() const;
    vector<byte> castDateToBin() const throw();

    //getters&setters
    string getIp();
    void setIp(string ip);
    int getLevel();
    void setLevel(int level);
    Time getTime();
    void setTime(Time time);

};
