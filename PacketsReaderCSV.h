#pragma once

#include "./PacketsReader.h"

using std::vector;

class PacketsReaderCSV : public PacketsReader
{
    protected:
        std::fstream file;

    public:
        PacketsReaderCSV(string filePath);
        ~PacketsReaderCSV();

        Packet getNextPacket();
};
