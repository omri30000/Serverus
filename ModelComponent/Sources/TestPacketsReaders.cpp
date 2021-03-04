#include "../Headers/PacketsReaderCSV.h"
#include "../Headers/PacketsReaderSQLITE.h"


//csv reader checker
/*
int maindds(){
    PacketsReaderCSV reader("sniffs.csv");

    try{
        while (true)
        {
            std::cout << reader.getNextPacket().toString() << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "finished reading packets" << std::endl;
    }

    return 0;
}


/*
//sqlite reader checker
int main(){
    PacketsReaderSQLITE reader("db_file.sqlite");

    try{
        while (true)
        {
            std::cout << reader.getNextPacket().toString() << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "finished reading packets" << std::endl;
    }
    return 0;
}
*/