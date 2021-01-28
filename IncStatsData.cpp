#include <thread>
#include "IncStatsData.h"

//constructor
IncStatsData::IncStatsData()
{
    _cleaningThread =  std::thread(&IncStatsData::cleanInactiveStats,this,10);
    _isRunning = true;
}

IncStatsData::~IncStatsData()
{
    _isRunning = false;
    _cleaningThread.join();

	for (map<string,vector<IncStats*>>::iterator it = this->_incStatsCollection.begin(); it != this->_incStatsCollection.end(); it++)
	{
		for (int i = 0; i < 5; i++)
		{
			delete it->second[i];
		}
	}

	for (map<string,vector<RelativeIncStats*>>::iterator it = this->_relIncStatsCollection.begin(); it != this->_relIncStatsCollection.end(); it++)
	{
		for (int i = 0; i < 5; i++)
		{
			delete it->second[i];
		}
	}
}

/*
 This function adds a new stream to the Category
 Input: uniqueKey -  The Stream Key : std::string
 Output: pointer to the vector of inc stats (with different lambda in each index)
 Throw: std::exception
 */
vector<IncStats*> IncStatsData::registerStream(string uniqueKey) throw()
{
	//check if not exists
	if(this->isStreamExists(uniqueKey))
		return this->_incStatsCollection.at(uniqueKey);
	
	//create 5 new incStats for the new stream

	const float lambdas[] = { 0.01,0.1,1,3,5 };
	std::vector<IncStats*> vec;

    for (size_t i = 0; i < 5; i++)
    {
        vec.push_back(new IncStats(uniqueKey, lambdas[i]));
    }

    this->_incStatsCollection.insert({ uniqueKey,vec });


	return vec;
}

/*
This function adds a new relative Inc stats to the main vector
Input: the keys of the two streams
Output: pointer to the vector of relative inc stats (with different lambda in each index)
Throw: std::exception
*/

vector<RelativeIncStats*> IncStatsData::registerRelatedStreams(string firstUniqueKey, string secondUniqueKey, Time timestamp) throw()
{
	string uniqueKey = this->getCombinedKey(firstUniqueKey,secondUniqueKey);;

    if (this->isRelStreamExists(uniqueKey))
    {
        return this->_relIncStatsCollection.at(uniqueKey);
    }

	vector<RelativeIncStats*> vec;
	std::vector<IncStats*> firstGroup = this->registerStream(firstUniqueKey);
	std::vector<IncStats*> secondGroup = this->registerStream(secondUniqueKey);

	//create new relative incremental statistics
	for (int i = 0 ; i < 5 ; i++) // for each lambda
	{
		vec.push_back(new RelativeIncStats(firstGroup[i], secondGroup[i], timestamp));
	}
	
	this->_relIncStatsCollection.insert({uniqueKey, vec});

	return vec;
}

/*
 This function inserts a new packet to the stream in all lambdas
 Input: key - the stream key : std::string
        value - the packet's value to enter : float
        timeStamp : the time stamp of the packet: Time
 Output: None
 Throw: std::exception
 */
void IncStatsData::insertPacket(string firstKey, string secondKey, float value, Time timestamp) throw()
{
    vector<RelativeIncStats*> vec = this->registerRelatedStreams(firstKey, secondKey, timestamp);

    for (int i = 0; i < this->_incStatsCollection[firstKey].size() ; ++i) // for each lambda
    {
        this->insertPacket(firstKey,value,timestamp,i);
    }

    for (int i = 0 ; i < vec.size(); i++)
    {
        vec[i]->update(firstKey, value, timestamp);
    }

}

/*
 This function inserts a new packet to the stream in a specific lambda
 Input: key - The stream key : std::string
        value - The packet's value to enter : float
        timeStamp : The time stamp of the packet: Time
        lambdaIndex : The index of the requested lambda
 Output: None
 Throw: std::exception
 */
void IncStatsData::insertPacket(string key, float value, Time timestamp, int lambdaIndex) throw()
{
	if (!this->isStreamExists(key))
        throw std::runtime_error("Stream doesn't exist");

	this->_incStatsCollection[key][lambdaIndex]->insertElement(value, timestamp);
}

/*

*/
void IncStatsData::insertPacket(string key, Time timestamp) throw()
{
    if (!this->isStreamExists(key))
        this->registerStream(key);

    for (int i = 0; i < this->_incStatsCollection[key].size() ; ++i)
    {
        this->_incStatsCollection[key][i]->insertElement(timestamp);
    }
}

/*
 This function gets stats of a specific stream of all lambdas
 Input: key - The stream key : std::string
 Output: all stats of stream : vector<float>
 Throw: std::exception
 */
vector<float> IncStatsData::getStatsOneDimension(string key) const throw()
{
	if (!this->isStreamExists(key))
        throw std::runtime_error("Stream doesn't exist");

	vector<float> result;
	for (size_t i = 0; i < this->_incStatsCollection.at(key).size() ; i++) // An iteration for each lambda index
	{
		vector<float> val = this->_incStatsCollection.at(key)[i]->getStats();
		for (float stat : val)
		{
			result.push_back(stat);
		}
	}
	return result;
}

/*
 This function gets stats of two specific streams of all lambdas
 Input: key - The stream key : std::string
 Output: all stats of stream : vector<float>
 Throw: std::exception
*/
vector<float> IncStatsData::getStatsTwoDimensions(string firstKey, string secondKey) const throw()
{
	string uniqueKey = this->getCombinedKey(firstKey,secondKey);
	if (!this->isRelStreamExists(uniqueKey))
	{
		throw std::runtime_error("the required link doesn't exist");
	}
	
	vector<float> result;
	for (size_t i = 0; i < this->_relIncStatsCollection.at(uniqueKey).size() ; i++)
	{
		vector<float> val = this->_relIncStatsCollection.at(uniqueKey)[i]->getRelativeStats();
		for (float stat : val)
		{
			result.push_back(stat);
		}
	}

	return result;
}

/*
 This function checks if a stream exists
 Input: key - The stream key : std::string
 Output: if the stream exists : bool
 */
bool IncStatsData::isStreamExists(string key) const
{
	try
	{
		this->_incStatsCollection.at(key);
	}
	catch (std::exception e)
	{
		return false;
	}
	return true;
}

bool IncStatsData::isRelStreamExists(string key) const
{
	try
	{
		this->_relIncStatsCollection.at(key);
	}
	catch (std::exception e)
	{
		return false;
	}
	return true;
}

string IncStatsData::getCombinedKey(string first, string second) const {
    if(first.compare(second) <0)
        return first +"+" + second;
    return second + "+" + first;
}


/*
The function will remove the streams with a weight lower than the limit from their containers.
This is a thread that will do his job once per X time
input: the limit, each stream with a weight lower than the limit will be removed
output: none
*/
void IncStatsData::cleanInactiveStats(float limit)
{
    while(_isRunning)
    {
        std::this_thread::sleep_for(std::chrono::minutes (20));
        const lock_guard<mutex> collectionLock(this->_incStatsCollectionLock);

        vector<string> toRemove;
        //find
        for(auto stream : _incStatsCollection)
        {
            for (int i = 0; i < stream.second.size(); ++i)
            {
                if(stream.second[i]->getWeight() < limit && (Time(1) - stream.second[i]->getLastTime() ) > Time::DAY)
                {
                    // last time > day
                    toRemove.push_back(stream.first);
                    break;
                }
           }
        }
        for(string remove : toRemove)
        {
            this->deleteStream(remove);

            for (auto it : _relIncStatsCollection)
            {
                string secondPart;
                int find = it.first.find(remove);
                int plus = it.first.find('+');

                if (find != string::npos)
                {
                    for (int i = 0; i < it.second.size(); ++i)
                    {
                        delete it.second[i];
                    }

                    //current is the first in key
                    if(find == 0)
                        secondPart =it.first.substr(plus+1,it.first.size() - plus-1);
                    else
                        secondPart = it.first.substr(0,plus);

                    this->deleteStream(secondPart);
                    break;
                }

            }
        }

    }
}

void IncStatsData::deleteStream(string key)
{
    if(!this->isStreamExists(key))
        return;
    map<string,vector<IncStats*>>::iterator it =_incStatsCollection.find(key) ;
    for (int i = 0; i < it->second.size(); ++i)
    {
        delete it->second[i];
    }
    _incStatsCollection.erase(it);

}
