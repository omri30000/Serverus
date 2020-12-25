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