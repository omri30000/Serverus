//
// Created by Omri Zaiman on 03/02/2021.
//

#include "../Headers/Event.h"

/*
Constructor
*/
Event::Event(string ip, int level, Time date)
{
    this->_ipAddr = ip;
    this->_level = level;
    this->_date = date;
}

/*
The function will cast this event to a binary sequence of 9 bytes contains the data for the defender
input: none
output: vector of bytes that represents the specific event
*/
vector<byte> Event::castToBinMessage() const throw()
{
    vector<byte> data;

    vector<byte> ipVec = this->castIpToBin();
    vector<byte> dateVec = this->castDateToBin();
    // insert level to the first byte
    data.push_back(this->_level);
    //insert IP address to the next 4 bytes
    data.insert(data.end(), ipVec.begin(), ipVec.end());
    //insert the date to the next 4 bytes
    data.insert(data.end(), dateVec.begin(), dateVec.end());

    return data;
}

/*
The function will calculate the time difference between the moment that the event occurred in
 and the beginning of the day (00:00)
input: none
output: the time difference in milliseconds
*/
int Event::calcDateMilliseconds() const
{
    return this->_date.getHour() * 60 * 60 * 1000 +
    this->_date.getMinute() * 60 * 1000 +
    this->_date.getSecond() * 1000 +
    this->_date.getMiliSec();
}

/*
The function will cast this event's IP address to a binary vector (4 bytes)
input: none
output: binary vector represents the IP
*/
vector<byte> Event::castIpToBin() const
{
    vector<byte> ipVec;
    string ip = this->_ipAddr; // 1.1.1.1
    string delimiter = ".";
    size_t pos = 0;
    string temp;

    while ((pos = ip.find(delimiter)) != string::npos) {
        temp = ip.substr(0, pos);
        ipVec.push_back(std::stoi(temp));
        ip.erase(0, pos + delimiter.length());
    }

    return ipVec;
}

/*
The function will cast this event's date address to a binary vector (4 bytes)
input: none
output: binary vector represents the date
*/
vector<byte> Event::castDateToBin() const throw()
{
    const int BASE = 256;
    const int BYTE_SIZE = 8;
    const int BYTES_AMOUNT = 4;

    vector<byte> vec = { 0, 0, 0, 0 };
    int millisec = this->calcDateMilliseconds();

    if (millisec > std::pow(BYTE_SIZE,BYTES_AMOUNT))
    {
        throw std::runtime_error("date value is invalid");
    }

    for (int i = vec.size() - 1; i >= 0; i--)
    {
        vec[i] = millisec % BASE;
        millisec /= BASE;
    }

    return vec;
}

//getters&setters
string Event::getIp() {return this->_ipAddr; }
void Event::setIp(string ip) { this->_ipAddr = ip; }
int Event::getLevel() { return this->_level; }
void Event::setLevel(int level) {this->_level = level; }
Time Event::getTime() { return this->_date; }
void Event::setTime(Time time) { this->_date = time; }