#include "./PacketsReaderCSV.h"

int main(){
    PacketsReaderCSV reader("Sniffs.csv");

    std::cout << reader.getNextPacket().toString() << std::endl;
    std::cout << reader.getNextPacket().toString() << std::endl;
    std::cout << reader.getNextPacket().toString() << std::endl;

    return 0;
}
