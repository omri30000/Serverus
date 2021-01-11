#include <iostream>
#include <string>


#include "PacketsReaderSQLITE.h"
#include "FeatureExtractor.h"
#include "FeatureMapper.h"
#include "Parser.h"

#include <cstdlib>

/*
void readPackets(string filePath);

void readPackets(string filePath)
{

    PacketsReader* pPackets = nullptr;
    //if .sqlite


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

}
*/

int main()
{
    srand (time(NULL));
    std::cout << "Hello, World!" << std::endl;
    PacketsReaderSQLITE reader =  PacketsReaderSQLITE("../db_file.sqlite");
    FeatureExtractor extractor;
    FeatureMapper mapper(300,15,45);
    //Parser* p

    while(true)
    {
        Packet pack;
        bool cond = false;
        while(!cond)
        {
            try {
                pack = reader.getNextPacket();
                cond = true;
            }
            catch (std::exception &e) {
                cond = false;
            }
        }

        std::cout<<pack.toString();
        vector<float> stats = extractor.extractNewFeaturesVector(pack);
        std::cout<<stats.size();
        for (int i = 0; i <stats.size() ; ++i)
        {
            //if(stats[i] == 0)
            //    stats[i] = (float)( rand() % 1000)/1000;
            std::cout << stats[i] <<',';
        }

        std::cout<<std::endl;
        if(!mapper.getState())
            mapper.update(stats);
        else
            std::cout<<mapper.cluster().second;
    }

    return 0;
}
