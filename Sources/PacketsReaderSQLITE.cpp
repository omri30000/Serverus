#include <thread>
#include "../Headers/PacketsReaderSQLITE.h"
//constructor
PacketsReaderSQLITE::PacketsReaderSQLITE(string filePath) :PacketsReader(filePath)
{
    int status = 0;
    this->_lastDate = "0000-00-00 00:00:00.000";
    status = sqlite3_open(filePath.c_str(), &this->_dbFile);
    sqlite3_exec(this->_dbFile, "pragma journal_mode = WAL", NULL, NULL, NULL);
    if (status) { 
        std::cerr << "Error open DB " << sqlite3_errmsg(this->_dbFile) << std::endl; 
        throw std::exception(); 
    } 
    else
        std::cout << "Opened Database Successfully!" << std::endl;
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
    string sqlStatement = "SELECT * FROM packets WHERE substr(arrival_time,0,24) > \"" + this->_lastDate
            + "\" ORDER BY arrival_time LIMIT 1";

    vector<string> record;

    executeCommand(sqlStatement.c_str(), callbackGetData, &record);

    if(record.size() == 0)
    {
        throw std::runtime_error("wow");
    }
    Packet p(record,1);
    this->_lastDate = p.getArrivalTime().toString();

    std::thread t =  std::thread(&PacketsReaderSQLITE::removeSeenPackets,this);
    t.detach();

    return p;
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
        //std::cout << "err " << res << std::endl;
		throw std::runtime_error("sqlite_error");
	}
}


void PacketsReaderSQLITE::removeOutgoingPackets()
{
    
    string hostMac, sqlStatement;
    int val = -1;
    
    hostMac = this->getHostMac();
    
    sqlStatement = "DELETE FROM packets WHERE source_mac = \'" + hostMac + "\'";

    executeCommand(sqlStatement.c_str(), callbackGetInt, &val);
}

void PacketsReaderSQLITE::removeSeenPackets()
{
    string sql = "DELETE FROM packets WHERE substr(arrival_time,0,24) < \"" + this->_lastDate + "\"";

    try
    {
        executeCommand(sql.c_str(), nullptr, nullptr);
        //std::cout<<"deleted"<<std::endl;
    }
    catch (std::exception &e)
    {
        //std::cout<<e.what()<<std::endl;
        return;
    }
}
