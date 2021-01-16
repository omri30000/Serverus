#include <iostream>
#include <string>


#include "PacketsReaderSQLITE.h"
#include "FeatureExtractor.h"
#include "FeatureMapper.h"
#include "Parser.h"
#include <cstdlib>

int main()
{
    srand (time(NULL));
    std::cout << "Hello, World!" << std::endl;
    PacketsReaderSQLITE reader =  PacketsReaderSQLITE("../db_file.sqlite");
    FeatureExtractor extractor;
    FeatureMapper mapper(10,15,45);
    Parser* p = nullptr;


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

        //std::cout<<pack.toString();
        vector<float> stats = extractor.extractNewFeaturesVector(pack);
        //std::cout<<stats.size();
        std::cout<<"#########\n";
        for (int i = 0; i <stats.size() ; ++i)
        {
            if(stats[i] == 0)
                stats[i] = (float)( rand() % 1000)/1000;
            //std::cout << stats[i] <<',';
        }

        std::cout<<std::endl;
        if(p == nullptr)
        {
            if(!mapper.getState())
                mapper.update(stats);
            else
            {

                vector<vector<int>> a  =mapper.cluster();
                p = new Parser(a);
                //exit(1);
            }
        }
        else
        {
            vector<vector<float>> a = p->organizeData(stats);
            for (int i = 0; i < a.size(); ++i) {
                for (int j = 0; j < a[i].size(); ++j) {
                    std::cout<< a[i][j] << ",";
                }
                std::cout<<std::endl;
            }

        }

    }

    return 0;
}
