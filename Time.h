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
    int _miliSec;

    int daysSinceYearStart();
    /*
    The Time class's c'tor
    #TODO: check time format comes from the data base
    */
public:
    Time() = default;
    Time(int year, int month, int day, int hour, int minute, int second, int miliSec);

    int operator-(const Time other)const;

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
    void setMiliSec(int miliSec);
    int getMiliSec() const;
}


