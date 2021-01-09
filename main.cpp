#include <iostream>
#include <string>
#include "PacketsReaderSQLITE.h"
#include "PacketsReaderCSV.h"
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

/*
##NOTE##
+ make sure you use sudo when running the program. the DB requires wirting permissions!
*/
int main()
{

    std::cout << "Hello, World!" << std::endl;
    //PacketsReaderSQLITE reader =  PacketsReaderSQLITE("../db_file.sqlite");
    PacketsReaderCSV reader("sniffs.csv");
    FeatureExtractor extractor;

    while(true)
    {
        Packet pack;
        bool cond = false;
        int countExceptions = 0;
        while(!cond)
        {
            try {
                if (countExceptions < 5)
                {
                    pack = reader.getNextPacket();
                    cond = true;
                }
                else{
                    std::cout << "Finished reading Packets" << std::endl;
                    return 0;
                }
            }
            catch (std::exception &e) {
                countExceptions++;
                cond = false;
            }
        }

        std::cout << pack.toString();
        vector<float> stats = extractor.extractNewFeaturesVector(pack);
        for (float v : stats)
        {
            std::cout << v << ',';
        }
        std::cout << std::endl;
    }

    return 0;
}
