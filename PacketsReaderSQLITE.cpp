#include "PacketsReaderSQLITE.h"

PacketsReaderSQLITE::PacketsReaderSQLITE(string filePath):PacketsReader(filePath)
{
    int status = 0; 
    status = sqlite3_open(filePath, &this->dbFile); 
  
    if (status) { 
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl; 
        throw std::exception(); 
    } 
    else
        std::cout << "Opened Database Successfully!" << std::endl; 
     
}

PacketsReaderSQLITE::~PacketsReaderSQLITE()
{
    sqlite3_close(this->dbFile);
}

Packet PacketsReaderSQLITE::getNextPacket() {
    //TODO: return the next packet
    return Packet();
}