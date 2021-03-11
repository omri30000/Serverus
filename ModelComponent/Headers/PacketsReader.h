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

        virtual void removeOutgoingPackets(){};
        
        static string execTerminalCommand(const char* cmd);

    public:
        PacketsReader(string filePath);
        virtual Packet getNextPacket() = 0;

        static string getHostMac();
};