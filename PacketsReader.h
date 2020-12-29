#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
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

    public:
        PacketsReader(string filePath);
        virtual Packet getNextPacket() = 0;

};