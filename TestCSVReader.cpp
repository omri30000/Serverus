#include "./PacketsReaderCSV.h"

int main(){
    PacketsReaderCSV reader("sniffs.csv");

    std::cout << reader.getNextPacket().toString() << std::endl;
    std::cout << reader.getNextPacket().toString() << std::endl;
    std::cout << reader.getNextPacket().toString() << std::endl;

    return 0;
}
