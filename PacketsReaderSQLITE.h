#pragma once

#include <sqlite3.h>
#include "PacketsReader.h"

//use these in terminal before compiling: 
//sudo apt-get install libsqlite3-dev
//sudo apt-get install sqlite3
class PacketsReaderSQLITE : PacketsReader
{
    protected:
        sqlite3* dbFile;

    public:
        PacketsReaderSQLITE(string filePath);
        ~PacketsReaderSQLITE();

        Packet getNextPacket();
};
