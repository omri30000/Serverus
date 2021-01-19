#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

#include "./Packet.h"

using std::string;

class PacketsReader
{
    /*
    This is an abstract PacketReader class
    */
    protected:
        int _cursor;
        string _dbFilePath;

        virtual void removeOutgoingPackets() = 0;
        
        string execTerminalCommand(const char* cmd);
        string getHostMac();
    public:
        PacketsReader(string filePath);
        virtual Packet getNextPacket() = 0;
        

};