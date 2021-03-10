#include "../Headers/Time.h"
#include <ctime>
#include <sstream>
#include <iomanip>

const int Time::DAY =24*60*60*1000;


Time::Time()
{
    this->_isFirst = true;

    //initialize these attributes for good looking while debugging
    this->_year = 0;
    this->_month = 0;
    this->_day = 0;
    this->_hour = 0;
    this->_minute = 0;
    this->_second = 0;
    this->_microSec = 0;
}
Time::Time(int i)
{
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);

    this->_year = now->tm_year +1900;
    this->_month = now->tm_mon+1;
    this->_day = now->tm_mday;
    this->_hour = now->tm_hour;
    this->_minute = now->tm_min;
    this->_second = now->tm_sec;
    this->_microSec = 0; // unnecessary
    this->_isFirst = false;

}

Time::Time(const Time& other)
{
    this->_isFirst = other._isFirst;
    this->_year = other.getYear();
    this->_month = other.getMonth();
    this->_day = other.getDay();
    this->_hour = other.getHour();
    this->_minute = other.getMinute();
    this->_second = other.getSecond();
    this->_microSec = other.getMicroSec();
}

Time::Time(int year, int month, int day, int hour, int minute, int second, int microSec)
{
    this->_isFirst = false;
    this->_year = year;
    this->_month = month;
    this->_day = day;
    this->_hour = hour;
    this->_minute = minute;
    this->_second = second;
    this->_microSec = microSec;
}


Time::Time(string time)
{
    //string argument example: "2020-12-28 13:49:10.987621"
    string t = time.substr(0, time.length() ); // "2020-12-28 13:49:10.987621"

    this->_year = std::stoi(t.substr(0, t.find('-'))); // 2020
    t = t.substr(t.find('-') + 1); // "12-28 13:49:10.987"

    this->_month = std::stoi(t.substr(0, t.find('-'))); // 12
    t = t.substr(t.find('-') + 1); // "28 13:49:10.987"

    this->_day = std::stoi(t.substr(0, t.find(' '))); // 28
    t = t.substr(t.find(' ') + 1); // "13:49:10.987"

    this->_hour = std::stoi(t.substr(0, t.find(':'))); // 13
    t = t.substr(t.find(':') + 1); // "49:10.987"

    this->_minute = std::stoi(t.substr(0, t.find(':'))); // 49
    t = t.substr(t.find(':') + 1); // "10.987"

    this->_second = std::stoi(t.substr(0, t.find('.'))); // 10
    t = t.substr(t.find('.') + 1); // "987621"

    this->_microSec = std::stoi(t); // 987621

    this->_isFirst = false;
}
/*
This function returns the difference between 2 time stamps in milliseconds()
Input: other - the other timeStamp : Time
Output: difference in millisecond : long
*/
long Time::operator-(const Time other) const
{
    if(other._isFirst || this->_isFirst)
        return 0;

    long diff = 0;
    diff += (this->_microSec - other._microSec)/1000;
    diff += (this->_second - other._second)*1000;
    diff += (this->_minute - other._minute) * 1000 * 60;
    diff += (this->_hour - other._hour) * 1000 * 60 * 60;
    diff += (this->daysSinceYearStart() - other.daysSinceYearStart()) * 1000 * 60 * 60 * 24;
    diff += (this->_year - other._year) * 1000 * 60 * 60 * 24 * 365;
    return diff;
}

/*

*/
Time& Time::operator= (const Time& other)
{
    this->_year = other._year;
    this->_month = other._month;
    this->_day = other._day;
    this->_hour = other._hour;
    this->_minute = other._minute;
    this->_second = other._second;
    this->_microSec = other._microSec;
    this->_isFirst = other._isFirst;

    return *this;
}

/*
This function returns the amount days since start of the year
Input:None
Output: Amount of years : int
*/
int Time::daysSinceYearStart() const {
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (!(this->_year % 4))
        days[1]++; //February +1
    int sum = 0;
    for (int i = 0; i < this->_month - 1; i++) {
        sum += days[i];
    }

    return sum + this->_day;
}

string Time::toString()
{
    string s = padNumber(this->_year,4) + "-" +
                padNumber(this->_month,2) + "-" +
                padNumber(this->_day,2) + " " +
                padNumber(this->_hour,2) + ":" +
                padNumber(this->_minute,2) + ":" +
                padNumber(this->_second,2) + "." +
                padNumber(this->_microSec,6);
    
    return s;
}

std::string padNumber(int val,int requiredLen)
{
    std::stringstream ss;
    ss << std::setw(requiredLen) << std::setfill('0') << val;
    return ss.str();
}

void Time::setYear(int year) { this->_year = year; } 
int Time::getYear() const { return this->_year; }
void Time::setMonth(int month) { this->_month = month; } 
int Time::getMonth() const { return this->_month; }
void Time::setDay(int day) { this->_day = day; } 
int Time::getDay() const { return this->_day; }
void Time::setHour(int hour) { this->_hour = hour; } 
int Time::getHour() const { return this->_hour; }
void Time::setMinute(int minute) { this->_minute = minute; } 
int Time::getMinute() const{ return this->_minute; }
void Time::setSecond(int second) { this->_second = second; } 
int Time::getSecond() const { return this->_second; }
void Time::setMicroSec(int microSec) { this->_microSec = microSec; }
int Time::getMicroSec() const{ return this->_microSec; }