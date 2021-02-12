#include <iostream>
#include <string>
#include <cstdlib>

#include "../Headers/PacketsReaderSQLITE.h"
#include "../Headers/FeatureExtractor.h"
#include "../Headers/FeatureMapper.h"
#include "../Headers/Parser.h"
#include "../Headers/Communicator.h"
#include "../Headers/AnomalyDetector.h"

// NOTE: Make sure to run program with sudo in order to be able to delete data from db
int main()
{
    srand (time(NULL));
    std::cout << "Hello, World!" << std::endl;
    PacketsReaderSQLITE reader = PacketsReaderSQLITE("../db_file.sqlite");
    FeatureExtractor extractor;
    FeatureMapper mapper(250,20,85);
    Parser* p = nullptr;
    AnomalyDetector* ad = nullptr; // todo: check if should be initialized

    //todo: Communicator communicator;

    bool cond = true;
    Packet pack;
    int a = 0;

    while (cond) {

        try {
            pack = reader.getNextPacket();
            std::cout << "a: " << a;
            a++;
        }
        catch (std::exception &e) {
            continue;
        }
        //std::cout<<pack.toString();
        vector<float> stats = extractor.extractNewFeaturesVector(pack);
        //std::cout<<stats.size();
        std::cout << "#########\n";
        for (int i = 0; i < stats.size(); ++i) {
            std::cout << stats[i] << ',';
        }
        std::cout << "\n-----------\n";

        std::cout << std::endl;

        if (p == nullptr) {
            if (!mapper.getState())
                mapper.update(stats);
            else {
                vector<vector<int>> a = mapper.cluster();
                std::cout << "Clusters amount: " << a.size() << std::endl;
                p = new Parser(a);
                //exit(1);
            }
        } else {
            valarray<valarray<float>> featuresMap = p->organizeData(stats);

            // print the mapped features
            for (int i = 0; i < featuresMap.size(); ++i) {
                for (int j = 0; j < featuresMap[i].size(); ++j) {
                    std::cout << featuresMap[i][j] << ",";
                }
                std::cout << std::endl;
            }

            ad = &ad->getInstance(85, 30, 0.1, 0.75, featuresMap);
            ad->perform(featuresMap);
        }
    }


    return 0;
}
