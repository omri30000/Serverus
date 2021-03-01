#pragma once

#include "Time.h"
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

class Packet
{
    private: 
        Time _arrivalTime;
        string _sourceMac;
        string _sourceIP;
        string _destIP;
        string _sourcePort;
        string _destPort;
        float _length;
        string _protocol;
        string _data;

    public:
        Packet(Time arrivalTime, string sourceMAC, string sourceIP, string destIP, string sourcePort,
            string destPort,float length, string protocol, string data);
        Packet(vector<string> record, int startIndex);//row of data from csv file
        Packet() = default; // remove this after building PacketsReaderSQLITE class

        string toString();

        //Set & Get
        void setArrivalTime(Time arrivalTime);
        Time getArrivalTime();
        void setSourceMac(string sourceIP);
        string getSourceMac();
        void setSourceIP(string sourceIP);
        string getSourceIP();
        void setDestIP(string destIP);
        string getDestIP();
        void setSourcePort(string sourcePort);
        string getSourcePort();
        void setDestPort(string destPort);
        string getDestPort();
        void setLength(int length);
        float getLength();
        void setProtocol(string protocol);
        string getProtocol();
        void setData(string data);
        string getData();
};