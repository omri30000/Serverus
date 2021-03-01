#include "../Headers/Packet.h"


Packet::Packet(Time arrivalTime, string sourceMAC,string destMAC ,string sourceIP, string destIP, string sourcePort,
            string destPort, float length, string protocol, string data)
{
    this->_arrivalTime = arrivalTime;
    this->_sourceMac = sourceMAC;
    this->_destMac = destMAC;
    this->_sourceIP = sourceIP;
    this->_destIP = destIP;
    this->_sourcePort = sourcePort;
    this->_destPort = destPort;
    this->_length = length;
    this->_protocol = protocol;
    this->_data = data;
}

Packet::Packet(vector<string> record, int startIndex)
{
    if (record.size() == 0) throw std::exception();

    this->_sourceMac = record[startIndex];
    this->_destMac = record[startIndex+1];
    this->_sourceIP = record[startIndex + 2];
    this->_destIP = record[startIndex + 3];
    this->_sourcePort = record[startIndex + 4];
    this->_destPort = record[startIndex + 5];
    this->_protocol = record[startIndex + 6];
    this->_length = std::stof(record[startIndex + 7]);
    this->_data = record[startIndex + 8];
    this->_arrivalTime = Time(record[startIndex + 9]);


    if(_sourcePort + _destPort == "") //there is no ports L3 and below
    {
        _sourcePort = _protocol;
        _destPort = _protocol;
    }
    if(_sourceIP + _destIP == "") //there is no ip's L2 and below
    {
        _sourceIP = _sourceMac;
        _destIP = _destMac;
    }



}

string Packet::toString()
{

    string s = "##PACKET##\n";
     s += this->_sourceMac + "\n";
     s += this->_sourceIP + "\n";
     s += this->_destIP + "\n"; 
     s += this->_sourcePort + "\n";
     s += this->_destPort + "\n";
     s += this->_protocol + "\n";
     s += std::to_string(this->_length) + "\n";
     s += this->_data + "\n";
     s += this->_arrivalTime.toString() + "\n";
     s += "##########\n";

    return s;
}


void Packet::setArrivalTime(Time arrivalTime) { this->_arrivalTime = arrivalTime; } 
Time Packet::getArrivalTime() { return this->_arrivalTime; }
void Packet::setSourceMac(string sourceMac) { this->_sourceMac = sourceMac; }
string Packet::getSourceMac() { return this->_sourceMac; }
void Packet::setSourceIP(string sourceIP) { this->_sourceIP = sourceIP; } 
string Packet::getSourceIP() { return this->_sourceIP; }
void Packet::setDestIP(string destIP) { this->_destIP = destIP; } 
string Packet::getDestIP() { return this->_destIP; }
void Packet::setSourcePort(string sourcePort) { this->_sourcePort = sourcePort; }
string Packet::getSourcePort() { return this->_sourcePort; }
void Packet::setDestPort(string destPort) { this->_destPort = destPort; }
string Packet::getDestPort() { return this->_destPort; }
void Packet::setLength(int length) { this->_length = length; } 
float Packet::getLength() { return this->_length; }
void Packet::setProtocol(string protocol) { this->_protocol = protocol; }
string Packet::getProtocol() { return this->_protocol; }
void Packet::setData(string data) { this->_data = data; } 
string Packet::getData() { return this->_data; }