#include "./PacketsReaderCSV.h"

int main(){
    PacketsReaderCSV reader("sniffs.csv");

    try{
        while (true)
        {
            std::cout << reader.getNextPacket().toString() << std::endl;
        }
    }
    catch (std::exception e)
    {
        std::cout << "finished reading packets" << std::endl;
    }

    return 0;
}
