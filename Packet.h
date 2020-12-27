#pragma once

#include "Time.h"
#include <string>

using std::string;

class Packet
{
    private: 
        Time _arrivalTime;
        string _sourceIP;
        string _destIP;
        int _sourcePort;
        int _destPort;
        int _length;
        bool _protocol;
        string _data;

    public:
        Packet(Time arrivalTime, string sourceIP, string destIP, int sourcePort, 
            int destPort, int length, bool protocol, string data);
        
        //Set & Get
        void setArrivalTime(Time arrivalTime);
        Time getArrivalTime();
        void setSourceIP(string sourceIP);
        string getSourceIP();
        void setDestIP(string destIP);
        string getDestIP();
        void setSourcePort(int sourcePort);
        int getSourcePort();
        void setDestPort(int destPort);
        int getDestPort();
        void setLength(int length);
        int getLength();
        void setProtocol(bool protocol);
        bool getProtocol();
        void setData(string data);
        string getData();
};