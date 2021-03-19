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

void killProcesses(const vector<string>& pNames);
void printUsage();

// NOTE: Make sure to run program with sudo in order to be able to delete data from db
int main(int argc, char **argv) {
    srand(time(NULL));
    std::cout << "Hello, World!" << std::endl;

    string filePath = "";
    TimeManager timeManager(false);

    bool forensics = false;
    bool disableOutgoing = true;
    bool threadExist = true;

    for (int i = 0; i < argc; ++i) {
        std::cout<<i<<". "<<argv[i]<<std::endl;
    }
    //parse commandline
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i],"-h") || !strcmp(argv[i], "--help"))
        {
            printUsage();
            return 0;
        }
        else if (!strcmp(argv[i] , "-f"))
        {

            if (i + 1 >= argc || argv[i + 1][0] == '-')
            {
                printUsage();
                return 0;
            }
            filePath = argv[i + 1];
            forensics = true;
            disableOutgoing = false;
            timeManager= TimeManager(true);
            i++;
        }
        else if(!strcmp(argv[i], "-o"))
        {
            //enbale outgoing packets
            disableOutgoing = false;
        }
        else if (!strcmp(argv[i],"-d"))
        {
            //cancel thread
            threadExist = false;
        }
        else
        {
            printUsage();
            return 0;
        }
    }

    //todo: if forensics dont run defender and don't run communicator - > how to block it
    TimeManager* pTimeManager;
    if(threadExist)
        pTimeManager = nullptr;
    else
        pTimeManager = &timeManager;

    killProcesses({"sniffer","defender"});

    system(("cd ../.. && sudo python3 SnifferComponent/SnifferToMQ.py "+ filePath+" > /dev/null &").c_str());
    if(!forensics)
        system("cd ../.. && sudo python3 DefenderComponent/Defender.py > /dev/null &");

    PacketsReaderMQ reader = PacketsReaderMQ();

    FeatureExtractor extractor(pTimeManager);

    FeatureMapper mapper(5000,7,85);
    Parser* p = nullptr;
    AnomalyDetector* ad = nullptr;

    std::ofstream file("values.txt");
    std::ofstream fileAnom("Anom.txt");

    Communicator communicator;


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
                continue;
            }

            timeManager.updateTime(pack.getArrivalTime());
            stats = extractor.extractNewFeaturesVector(pack);

            //remove outgoing packets - if needed
            if(disableOutgoing && pack.getSourceMac() == PacketsReader::getHostMac())
                continue;

        if (p == nullptr)
        {
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


            }
        }
        else
        {
            valarray<valarray<float>> featuresMap = p->organizeData(stats);


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
                    if (!forensics) {
                        extractor.deleteFromIncStats(pack);
                        communicator.sendMessage(Event(pack.getSourceIP(), val, pack.getArrivalTime()));

                    }
                }
            }
        }
    }
    return 0;
}
void printUsage()
{
    std::cout << "usage: model.exe [options]\n"
                <<"options:\n"
                <<" -f, for forenics - add file path after\n"
                <<"-d. cancel defence thread\n"
                <<"-o = enable outgoing packet\n";
}
void killProcesses(const vector<string>& pNames)
{
    for(string name : pNames)
    {
        system(("pkill -9 " +name).c_str());
    }

}
