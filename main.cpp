#include <iostream>
#include <string>
#include "PacketsReaderSQLITE.h"
#include "FeatureExtractor.h"

void readPackets(string filePath);

void readPackets(string filePath)
{

    PacketsReader* pPackets = nullptr;
    //if .sqlite
    /*

    pPackets = new PacketsReaderSQLITE();
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
     */
}


int main() {

    std::cout << "Hello, World!" << std::endl;
    PacketsReader * reader = new PacketsReaderSQLITE("path");
    FeatureExtractor extractor;

    while(true)
    {
        Packet* p = nullptr;
        Packet pack;
        bool cond = false;
        while(!cond) {
            try {
                pack = reader->getNextPacket();
                cond = true;
            }
            catch (std::exception &e) {
                cond = false;
            }
        }

        std::cout<<pack.toString();
        vector<float> stats = extractor.extractNewFeaturesVector(pack);\
        for (float v : stats)
        {
            std::cout << v<<',';
        }
        std::cout<<std::endl;
    }

    return 0;
}
