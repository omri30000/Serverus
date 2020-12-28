#include "PacketsReaderCSV.h"

PacketsReaderCSV::PacketsReaderCSV(string filePath):PacketsReader(filePath){
    //open the file
    this.file.open(filePath.c_str(), ios::in);

}

PacketsReaderCSV::~PacketsReaderCSV()
{
    this.file.close();
}

Packet PacketsReaderCSV::getNextPacket() {
    
    vector<string> row;
    string record, temp;

    this.file >> temp;
    
    record = "";

    getline(this.file, record);

    stringstream s(record);

    while(getline(s, word, ', '))
    {
        row.push_back(word);
    }

    return Packet(row);
}