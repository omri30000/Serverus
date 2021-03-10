#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>

#include "../Headers/PacketsReaderSQLITE.h"
#include "../Headers/FeatureExtractor.h"
#include "../Headers/FeatureMapper.h"
#include "../Headers/Parser.h"
#include "../Headers/Communicator.h"
#include "../Headers/AnomalyDetector.h"
#include "../Headers/utils.h"
#include "../Headers/Manipulator.h"
#include <fstream>

// NOTE: Make sure to run program with sudo in order to be able to delete data from db
int main()
{
    srand (time(NULL));
    std::cout << "Hello, World!" << std::endl;
    PacketsReaderSQLITE reader = PacketsReaderSQLITE("../../../db_mirai.sqlite");
    FeatureExtractor extractor;
    FeatureMapper mapper(5000,10,85);
    Parser* p = nullptr;
    AnomalyDetector* ad = nullptr;
    std::ofstream file("values.txt");

    Communicator communicator;
    float min = 5;
    float max = -5;

    bool cond = true;
    Packet pack;
    int a = 0;
    float maxThreshold=0;
    Manipulator* manipulator = nullptr;
    vector<vector<float>> _learningValues;
    while (cond) {
        vector<float> stats;
        if (a <= 55000 || _learningValues.size() == 0) {
            try {
                pack = reader.getNextPacket();

                a++;

            }
            catch (std::exception &e) {
                //std::cout<<"been here"<<std::endl;
                continue;
            }
           stats = extractor.extractNewFeaturesVector(pack);
            if(a > 5000 &&  a<=55000)
                _learningValues.push_back(stats);
        }
        else
        {
            stats = _learningValues[0];
            _learningValues.erase(_learningValues.begin());
            a++;
        }


        if (p == nullptr) {
            if (!mapper.getState())
                mapper.update(stats);
            else {
                vector<vector<int>> vec = mapper.cluster();
                //std::cout << "Clusters amount: " << vec.size() << std::endl;
                p = new Parser(vec);
                vector<int> size;

                for (int i = 0; i <vec.size() ; ++i)
                {
                    size.push_back(vec[i].size());
                }
                ad = &AnomalyDetector::getInstance(85, 50000, 0.05, 0.75, size);

                //exit(1);
            }
        }
        else {
            valarray<valarray<float>> featuresMap = p->organizeData(stats);


            // print the mapped features


            std::pair<float,bool> result = ad->perform(featuresMap);
            if(result.second)
                maxThreshold = std::max(maxThreshold,result.first);
            else
            {
                if(manipulator == nullptr)
                    manipulator = new Manipulator(maxThreshold);
                file<<result.first<<"---"<<a<<std::endl;
                int val = manipulator->calcLevel(result.first);
                if(val != 0)
                    std::cout<<"Anomaly: "<<val << " Num: "<<a<<std::endl;
                    //communicator.sendMessage(Event(pack.getSourceIP(),val,pack.getArrivalTime()));
            }
        }
    }
    return 0;
}
