#pragma once

#include <sqlite3.h>
#include "PacketsReader.h"

//use these in terminal before compiling: 
//sudo apt-get install libsqlite3-dev
//sudo apt-get install sqlite3
//add this to makeFile flags:
//-lsqlite3
class PacketsReaderSQLITE : PacketsReader
{
    protected:
        sqlite3* _dbFile;
        
        static int callbackGetData(void* data, int argc, char** argv, char** azColName);
        void executeCommand(const char* statement, int (*callback)(void*, int, char**, char**), void* arg);
    
    public:
        PacketsReaderSQLITE(string filePath);
        ~PacketsReaderSQLITE();
           
        Packet getNextPacket();
};
