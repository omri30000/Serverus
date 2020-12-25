#pragma once

#include <map>
#include <string>

//TODO: add local includes

using std::map;
using std::string;

class IncStatsData
{
protected:

    map<string,IncStats> _incStatsCollection;
    
    //addIncStats();
    //RelativeIncStats addRelativeIncStats();
public:
    IncStatsData();

}