#include <iostream>
#include "./PacketsReaderCSV.h"
#include "./PacketsReaderSQLITE.h"
#include "FeatureExtractor.h"

int main() {
    PacketsReaderSQLITE reader("db_file.sqlite");
    FeatureExtractor fe;
    

    try{
        while (true)
        {
            Packet p = reader.getNextPacket();
            std::cout << p.toString() << std::endl;
            std::vector<float> features = fe.extractNewFeaturesVector(p);

            for (float v : features)
            {
                std::cout << v  << ", ";
                
            }
            std::cout << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "finished reading packets" << std::endl;
    }
    return 0;
}