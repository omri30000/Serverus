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

    this->file >> temp;
    
    record = "";

    std::getline(this->file, record, '\n');

    std::stringstream stream(record);

    while(std::getline(stream, word, ','))
    {
        row.push_back(word);
    }

    return Packet(row);
}