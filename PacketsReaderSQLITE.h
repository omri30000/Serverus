#pragma once

#include "PacketsReader.h"

class PacketsReaderSQLITE : PacketsReader
{
public:
    PacketsReaderSQLITE(string filePath);
    Packet getNextPacket();
};
