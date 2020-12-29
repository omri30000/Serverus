#include "PacketsReaderCSV.h"

PacketsReaderCSV::PacketsReaderCSV(string filePath):PacketsReader(filePath){
    //open the file
    this->file.open(filePath.c_str(), std::fstream::in);

}

PacketsReaderCSV::~PacketsReaderCSV()
{
    this->file.close();
}

Packet PacketsReaderCSV::getNextPacket() {
    
    vector<string> row;
    string record, temp, word;

    if (this->_cursor == 0)
    {
        this->file >> temp;  
        this->_cursor++;
    }

    this->file >> record;
    this->file >> temp;
    record += (" " + temp);

    this->_cursor++;
    //std::cout << record << std::endl;
    std::stringstream stream(record);

    while(std::getline(stream, word, ','))
    {
        row.push_back(word);
    }

    return Packet(row);
}