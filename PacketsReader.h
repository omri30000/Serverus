#pragma once

#include <string>
#include "Packet.h"

using std::string;

class PacketsReader
{
    private:
        int _cursor;
        string _dbFilePath;

    public:
        PacketsReader();
        Packet getNextPacket();

}