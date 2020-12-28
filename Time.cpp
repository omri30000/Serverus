#include "Time.h"

Time::Time(int year, int month, int day, int hour, int minute, int second, int miliSec)
{
    this->_year = year;
    this->_month = month;
    this->_day = day;
    this->_hour = hour;
    this->_minute = minute;
    this->_second = second;
    this->_miliSec = miliSec;
}

Time::Time(string time)
{
    //string argument example: "2020-12-28 13:49:10.987621"
    string t = time.substr(0, time.length() - 3); // "2020-12-28 13:49:10.987"

    this->_year = stoi(t.substr(0, t.find('-'))); // 2020
    t = t.substr(t.find('-')); // "12-28 13:49:10.987"

    this->_month = stoi(t.substr(0, t.find('-'))); // 12
    t = t.substr(t.find('-') + 1); // "28 13:49:10.987"

    this->_day = stoi(t.substr(0, t.find(' '))); // 28
    t = t.substr(t.find(' ') + 1); // "13:49:10.987"

    this->_hour = stoi(t.substr(0, t.find(':'))); // 13
    t = t.substr(t.find(':') + 1); // "49:10.987"

    this->_minute = stoi(t.substr(0, t.find(':'))); // 49
    t = t.substr(t.find(':') + 1); // "10.987"

    this->_second = stoi(t.substr(0, t.find('.'))); // 10
    t = t.substr(t.find('.') + 1); // "987"

    this->_miliSec = stoi(t); // 987
}

string Time::toString()
{
    string s = std::to_string(this->_year) + "-" +
                std::to_string(this->_month) + "-" +
                std::to_string(this->_day) + " " +
                std::to_string(this->_hour) + ":" +
                std::to_string(this->_minute) + ":" +
                std::to_string(this->_second) + "." +
                std::to_string(this->_miliSec);

    return s;
}

void Time::setYear(int year) { this->_year = year; } 
int Time::getYear() { return this->_year; }
void Time::setMonth(int month) { this->_month = month; } 
int Time::getMonth() { return this->_month; }
void Time::setDay(int day) { this->_day = day; } 
int Time::getDay() { return this->_day; }
void Time::setHour(int hour) { this->_hour = hour; } 
int Time::getHour() { return this->_hour; }
void Time::setMinute(int minute) { this->_minute = minute; } 
int Time::getMinute() { return this->_minute; }
void Time::setSecond(int second) { this->_second = second; } 
int Time::getSecond() { return this->_second; }
void Time::setMiliSec(int miliSec) { this->_miliSec = miliSec; } 
int Time::getMiliSec() { return this->_miliSec; }