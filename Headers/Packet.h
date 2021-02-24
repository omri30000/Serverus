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
        int _sourcePort;
        int _destPort;
        float _length;
        bool _protocol;
        string _data;

    public:
        Packet(Time arrivalTime, string sourceMAC, string sourceIP, string destIP, int sourcePort,
            int destPort,float length, bool protocol, string data);
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
        void setSourcePort(int sourcePort);
        int getSourcePort();
        void setDestPort(int destPort);
        int getDestPort();
        void setLength(int length);
        float getLength();
        void setProtocol(bool protocol);
        bool getProtocol();
        void setData(string data);
        string getData();
};