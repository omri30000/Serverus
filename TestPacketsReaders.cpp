#include "./PacketsReaderCSV.h"
#include "./PacketsReaderSQLITE.h"
#include "FeatureExtractor.h"
/*
//csv reader checker
int main(){
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
*/

/*
//sqlite reader checker
int main(){
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
*/