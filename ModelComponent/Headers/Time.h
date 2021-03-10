#pragma once

#include <string>
#include <iostream>

using std::string;

class Time {
private:

    int _year;
    int _month;
    int _day;
    int _hour;
    int _minute;
    int _second;
    int _microSec;

    bool _isFirst;

    int daysSinceYearStart() const;

public:
    Time();
    Time(int year, int month, int day, int hour, int minute, int second, int microSec);
    Time(string time);
    Time(const Time& other); // copy constructor

    long operator-(const Time other)const;
    Time& operator= (const Time& other);

    string toString();

    //Set & Get
    void setYear(int year);
    int getYear() const;
    void setMonth(int month);
    int getMonth() const;
    void setDay(int day);
    int getDay() const;
    void setHour(int hour);
    int getHour() const;
    void setMinute(int minute);
    int getMinute() const;
    void setSecond(int second);
    int getSecond() const;
    void setMicroSec(int miliSec);
    int getMicroSec() const;

    static const int DAY;

    Time(int i);
};

std::string padNumber(int val,int requiredLen);

