#pragma once

#include "PacketsReader.h"

class PacketsReaderCSV : PacketsReader
{
    public:
        PacketsReaderCSV(string filePath);
        virtual Packet getNextPacket();
};
