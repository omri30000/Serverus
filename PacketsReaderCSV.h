#pragma once


#include "PacketsReader.h"

using std::vector;

class PacketsReaderCSV : PacketsReader
{
    protected:
        fstream file;

    public:
        PacketsReaderCSV(string filePath);
        ~PacketsReaderCSV();

        virtual Packet getNextPacket();
};
