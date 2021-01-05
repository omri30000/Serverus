#include "PacketsReaderCSV.h"


PacketsReaderCSV::PacketsReaderCSV(string filePath):PacketsReader(filePath){
    //open the file
    this->file.open(filePath.c_str(), std::fstream::in);
}

PacketsReaderCSV::~PacketsReaderCSV()
{
    this->file.close();
    this->removeOutgoingPackets();
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

    return Packet(row, 1);
}

void PacketsReaderCSV::removeOutgoingPackets()
{
    
    // Open FIle pointers 
    std::fstream fin, fout; 
  
    // Open the existing file 
    fin.open(this->_dbFilePath, std::fstream::in); 
  
    // Create a new file to store the non-deleted data 
    fout.open("temp.csv", std::fstream::out); 
  
    int i;
    string line, word, hostMac; 
    vector<string> row; 
    
    int row_size = row.size(); 
    hostMac = this->getHostMac();

    // Check if this record exists 
    // If exists, leave it and 
    // add all other data to the new file 
    while (!fin.eof()) { 
  
        row.clear(); 
        getline(fin, line); 
        std::stringstream s(line); 
  
        while (getline(s, word, ',')) { 
            row.push_back(word); 
        }
  
        // writing all records, 
        // except the record to be deleted, 
        // into the new file 'reportcardnew.csv' 
        // using fout pointer 
        if (row[0].find(hostMac) == string::npos) {
            if (!fin.eof()) { 
                for (i = 0; i < row_size - 1; i++) { 
                    fout << row[i] << ", "; 
                } 
                fout << row[row_size - 1] << "\n"; 
            } 
        }
        if (fin.eof()) 
            break; 
    }

    // Close the pointers 
    fin.close(); 
    fout.close(); 
  
    // removing the existing file 
    remove(this->_dbFilePath.c_str()); 
  
    // renaming the new file with the existing file name 
    rename("temp.csv", this->_dbFilePath.c_str());
}