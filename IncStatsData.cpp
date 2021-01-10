#include "IncStatsData.h"

//constructor
IncStatsData::IncStatsData()
{

}

/*
 This function adds a new stream to the Category
 Input: uniqueKey -  The Stream Key : std::string
 Output: None
 Throw: std::exception
 */
void IncStatsData::registerStream(string uniqueKey) throw()
{
	//check if not exists
	if(this->isStreamExists(uniqueKey))
		throw std::runtime_error("Stream already exists");
	

	const float lambdas[] = { 0.01,0.1,1,3,5 };
	std::vector<IncStats> vec;
	for (size_t i = 0; i <5; i++)
	{
		vec.push_back(IncStats(uniqueKey, lambdas[i]));
	}
	this->_incStatsCollection.insert({ uniqueKey,vec });
}

/*

*/
void IncStatsData::registerRelatedStreams(string firstUniqueKey, string secondUniqueKey) throw()
{
	float lambda = 0; // FIX

	firstIncStats = 
}

/*
 This function inserts a new packet to the stream in all lambdas
 Input: key - the stream key : std::string
        value - the packet's value to enter : float
        timeStamp : the time stamp of the packet: Time
 Output: None
 Throw: std::exception
 */
void IncStatsData::insertPacket(string key, float value, Time timestamp) throw()
{

    if (!this->isStreamExists(key))
        this->registerStream(key);

    for (int i = 0; i <this->_incStatsCollection[key].size() ; ++i)
    {
        this->insertPacket(key,value,timestamp,i);
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

	this->_incStatsCollection[key][lambdaIndex].insertElement(value, timestamp);
}

/*
 This function gets stats of a specific stream of all lambdas
 Input: key - The stream key : std::string
 Output: all stats of stream : vector<float>
 Throw: std::exception
 */
vector<float> IncStatsData::getStats(string key) const throw()
{
	if (!this->isStreamExists(key))
        throw std::runtime_error("Stream doesn't exist");

	vector<float> result;
	for (size_t i = 0; i < this->_incStatsCollection.at(key).size() ; i++)
	{
		vector<float> val = this->_incStatsCollection.at(key)[i].getStats();
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


void IncStatsData::insertPacket(string key, Time timestamp) throw()
{
    if (!this->isStreamExists(key))
        this->registerStream(key);

    for (int i = 0; i <this->_incStatsCollection[key].size() ; ++i)
    {
        this->_incStatsCollection[key][i].insertElement(timestamp);
    }
}
