#include "PacketsReaderCSV.h"


PacketsReaderCSV::PacketsReaderCSV(string filePath):PacketsReader(filePath){
    //open the file
    this->file.open(filePath.c_str(), std::fstream::in);
}

PacketsReaderCSV::~PacketsReaderCSV()
{
    this->file.close();
}

/*
The function will read a packet out of the sniffs file
input: none
output: Packet object represents the packet that was read
*/
Packet PacketsReaderCSV::getNextPacket() {
    
    vector<string> row;
    string record, temp, word;

    //The first line is the titles so it has to be ignored
    if (this->_cursor == 0)
    {
        this->file >> temp;
        this->_cursor++;
    }

    //combine the record
    this->file >> record;
    this->file >> temp;
    record += (" " + temp);

    //increment the cursor that points on the current packet index
    this->_cursor++;
    
    std::stringstream stream(record);
    if (stream.str().find_first_of(',', 0) != std::string::npos)
    {
        while(std::getline(stream, word, ','))
        {
            row.push_back(word);
        }
    }
    else
    {
        throw std::exception();
    }

    return Packet(row);
}