#pragma once

#include "./PacketsReader.h"

using std::vector;

class PacketsReaderCSV : public PacketsReader
{
    protected:
        std::fstream file;

        void removeOutgoingPackets();
    public:
        PacketsReaderCSV(string filePath);
        ~PacketsReaderCSV();

        Packet getNextPacket();
};
