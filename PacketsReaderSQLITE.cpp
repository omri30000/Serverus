#include "PacketsReaderSQLITE.h"
//constructor
PacketsReaderSQLITE::PacketsReaderSQLITE(string filePath) :PacketsReader(filePath)
{
    int status = 0;
    this->_cursor = 0;

    status = sqlite3_open(filePath.c_str(), &this->_dbFile); 
  
    if (status) { 
        std::cerr << "Error open DB " << sqlite3_errmsg(this->_dbFile) << std::endl; 
        throw std::exception(); 
    } 
    else
        std::cout << "Opened Database Successfully!" << std::endl; 

    this->_cursor = this->find_next_row();
}

//destructor
PacketsReaderSQLITE::~PacketsReaderSQLITE()
{
    //std::cout << "PRSQLITE DETOR" << std::endl;
    this->removeOutgoingPackets();
    sqlite3_close(this->_dbFile);
    //std::cout << "finsh PRSQLITE DETOR" << std::endl;
}


Packet PacketsReaderSQLITE::getNextPacket() {
    string sqlStatement = "SELECT * FROM packets WHERE id = " + std::to_string(this->_cursor);
    vector<string> record;

    executeCommand(sqlStatement.c_str(), callbackGetData, &record);

    if(record.size() == 0)
    {
        throw std::exception();
    }

    this->_cursor = this->find_next_row();

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
The function will return single int value,
input: the char** base arr, number of fields, strings with the data, strings with fields names
*/
int PacketsReaderSQLITE::callbackGetInt(void* data, int argc, char** argv, char** azColName)
{
    if(argv[0] != 0)
        *(int*)data = std::stoi(argv[0]);
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
        std::cout << "err " << res << std::endl;
		throw std::exception();
	}
}

/*
 This function returns the id of the next unread row in the db
 Input:None
 Output:ID of the next unread record in db, if none new record - return the current cursor value
 */
int PacketsReaderSQLITE::find_next_row() {
    string sqlStatement = "SELECT MIN(id) FROM packets WHERE id > " + std::to_string(this->_cursor) ;
    int val = -1;

    executeCommand(sqlStatement.c_str(), callbackGetInt, &val);

    return  val != -1 ? val : this->_cursor+1;
}


void PacketsReaderSQLITE::removeOutgoingPackets()
{
    
    string hostMac, sqlStatement;
    int val = -1;
    
    hostMac = this->getHostMac();
    
    sqlStatement = "DELETE FROM packets WHERE source_mac = \'" + hostMac + "\'";
    
    executeCommand(sqlStatement.c_str(), callbackGetInt, &val);
}