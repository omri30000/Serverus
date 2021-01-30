#include <iostream>
#include <string>


#include "../Headers/PacketsReaderSQLITE.h"
#include "../Headers/FeatureExtractor.h"
#include "../Headers/FeatureMapper.h"
#include "../Headers/Parser.h"
#include <cstdlib>

// NOTE: Make sure to run program with sudo in order to be able to delete data from db
int main()
{
    srand (time(NULL));
    std::cout << "Hello, World!" << std::endl;
    PacketsReaderSQLITE reader = PacketsReaderSQLITE("../db_file.sqlite");
    FeatureExtractor extractor;
    FeatureMapper mapper(250,20,85);
    Parser* p = nullptr;



    bool cond = true;
    Packet pack;
    int a = 0;
    try
    {
        pack = reader.getNextPacket();
    }
    catch (std::exception &e) {
        cond = false;
    }
    while (cond) {
        a++;
        if(a > 250)
            a++;
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
            else
                {
                vector<vector<int>> a = mapper.cluster();
                std::cout<<"Clusters amount: " <<a.size()<<std::endl;
                p = new Parser(a);
                //exit(1);
            }
        } else {
            vector<vector<float>> a = p->organizeData(stats);
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[i].size(); ++j) {
                    std::cout << a[i][j] << ",";
                }
                std::cout << std::endl;
            }

        }

        try {
            pack = reader.getNextPacket();
        }
        catch (std::exception &e) {
            cond = false;
        }
    }
    return 0;
}
