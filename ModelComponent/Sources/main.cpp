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
#include "../Headers/TimeManager.h"
#include "../Headers/PacketsReaderMQ.h"


// NOTE: Make sure to run program with sudo in order to be able to delete data from db
int main(int argc, char **argv)
{
    srand (time(NULL));
    std::cout << "Hello, World!" << std::endl;

    string filePath = "../../db_file.sqlite";
    TimeManager timeManager(false);

    if(argc>=1)
    {
        timeManager = TimeManager(true);
    }

    //PacketsReaderSQLITE reader = PacketsReaderSQLITE(filePath);
    PacketsReaderMQ reader = PacketsReaderMQ();
    FeatureExtractor extractor(&timeManager);

    FeatureMapper mapper(5000,7,85);
    Parser* p = nullptr;
    AnomalyDetector* ad = nullptr;

    std::ofstream file("values.txt");
    std::ofstream fileAnom("Anom.txt");

    Communicator communicator;
    float min = 5;
    float max = -5;

    bool cond = true;
    Packet pack;
    int a = 0;
    float maxThreshold=0;
    Manipulator* manipulator = nullptr;
    int t0 = time(NULL);


    while (cond) {
        vector<float> stats;
        try {
                pack = reader.getNextPacket();
                a++;
                if(a%1000 ==0)
                {
                    std::cout << a <<" ";
                    int t1 = time(NULL);
                    std::cout<<t1-t0<<std::endl;
                    t0 = t1;
                }
            }
            catch (std::exception &e) {
                //std::cout<<"been here"<<std::endl;
                continue;
            }

            timeManager.updateTime(pack.getArrivalTime());
            stats = extractor.extractNewFeaturesVector(pack);

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
                ad = &AnomalyDetector::getInstance(85, 50000, 0.1, 0.75, size);

                //exit(1);
            }
        }
        else
        {
            valarray<valarray<float>> featuresMap = p->organizeData(stats);


            // print the mapped features


            std::pair<float,bool> result = ad->perform(featuresMap);
            if(result.second)
                maxThreshold = std::max(maxThreshold,result.first);

            else {
                if (manipulator == nullptr)
                    manipulator = new Manipulator(maxThreshold);

                file << result.first << "---" << a << std::endl;
                int val = manipulator->calcLevel(result.first);
                if (val != 0) {
                    fileAnom << "Anomaly: " << val << " Num: " << a << std::endl;
                    extractor.deleteFromIncStats(pack);
                    //communicator.sendMessage(Event(pack.getSourceIP(),val,pack.getArrivalTime()));*/
                }
            }
        }
    }
    return 0;
}
