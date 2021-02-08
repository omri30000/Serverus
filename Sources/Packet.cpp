#include "../Headers/Packet.h"


Packet::Packet(Time arrivalTime, string sourceIP, string destIP, int sourcePort, 
            int destPort, float length, bool protocol, string data)
{
    this->_arrivalTime = arrivalTime;
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

    this->_sourceIP = record[startIndex];
    this->_destIP = record[startIndex + 1];
    this->_sourcePort = std::stoi(record[startIndex + 2]);
    this->_destPort = std::stoi(record[startIndex + 3]);
    this->_protocol = (record[startIndex + 4] == "UDP" || record[startIndex + 4] == "TCP");
    this->_length = std::stof(record[startIndex + 5]);
    this->_data = record[startIndex + 6];
    this->_arrivalTime = Time(record[startIndex + 7]); 


}

string Packet::toString()
{

    string s = "##PACKET##\n";
     s += this->_sourceIP + "\n";
     s += this->_destIP + "\n"; 
     s += std::to_string(this->_sourcePort) + "\n";
     s += std::to_string(this->_destPort) + "\n"; 
     s += std::to_string(this->_protocol) + "\n";
     s += std::to_string(this->_length) + "\n";
     s += this->_data + "\n";
     s += this->_arrivalTime.toString() + "\n";
     s += "##########\n";

    return s;
}


void Packet::setArrivalTime(Time arrivalTime) { this->_arrivalTime = arrivalTime; } 
Time Packet::getArrivalTime() { return this->_arrivalTime; }
void Packet::setSourceIP(string sourceIP) { this->_sourceIP = sourceIP; } 
string Packet::getSourceIP() { return this->_sourceIP; }
void Packet::setDestIP(string destIP) { this->_destIP = destIP; } 
string Packet::getDestIP() { return this->_destIP; }
void Packet::setSourcePort(int sourcePort) { this->_sourcePort = sourcePort; } 
int Packet::getSourcePort() { return this->_sourcePort; }
void Packet::setDestPort(int destPort) { this->_destPort = destPort; } 
int Packet::getDestPort() { return this->_destPort; }
void Packet::setLength(int length) { this->_length = length; } 
float Packet::getLength() { return this->_length; }
void Packet::setProtocol(bool protocol) { this->_protocol = protocol; } 
bool Packet::getProtocol() { return this->_protocol; }
void Packet::setData(string data) { this->_data = data; } 
string Packet::getData() { return this->_data; }