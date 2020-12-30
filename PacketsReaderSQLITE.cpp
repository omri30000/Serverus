#include "PacketsReaderSQLITE.h"

PacketsReaderSQLITE::PacketsReaderSQLITE(string filePath):PacketsReader(filePath)
{
    int status = 0; 
    status = sqlite3_open(filePath.c_str(), &this->_dbFile); 
  
    if (status) { 
        std::cerr << "Error open DB " << sqlite3_errmsg(this->_dbFile) << std::endl; 
        throw std::exception(); 
    } 
    else
        std::cout << "Opened Database Successfully!" << std::endl; 

    this->_cursor = 1;
}

PacketsReaderSQLITE::~PacketsReaderSQLITE()
{
    sqlite3_close(this->_dbFile);
}

Packet PacketsReaderSQLITE::getNextPacket() {
    string sqlStatement = "SELECT * FROM packets WHERE id = " + std::to_string(this->_cursor);
    vector<string> record;

    executeCommand(sqlStatement.c_str(), callbackGetData, &record);
    this->_cursor++;
    
    return Packet(record, 2);
}

/*
The function will return one record represents a packet, in a vector<string> structure
input: the char** base arr, number of fields, strings with the data, strings with fields names
*/
int PacketsReaderSQLITE::callbackGetData(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
        ((vector<string>*)data)->push_back(string(argv[i]));
	}

	return 0;
}


/*
The function will get sql statement and execute it on the db of the class
input: sql statement, a callback function
output: true or false if everything went fine
*/
void PacketsReaderSQLITE::executeCommand(const char* statement, int (*callback)(void*, int, char**, char**), void* arg)
{
	int res = 0;

	char** errMessage = nullptr;
	res = sqlite3_exec(this->_dbFile, statement, callback, arg, errMessage);

	if (res != SQLITE_OK)
	{
		throw std::exception();
	}
}

