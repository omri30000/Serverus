#include "IncStatsData.h"

//constructor
IncStatsData::IncStatsData()
{

}

/*
 This function adds a new stream to the Category
 Input: uniqueKey -  The Stream Key : std::string
 Output: pointer to the vector of inc stats (with different lambda in each index)
 Throw: std::exception
 */
vector<IncStats>* IncStatsData::registerStream(string uniqueKey) throw()
{
	//check if not exists
	if(this->isStreamExists(uniqueKey))
		return this->_incStatsCollection.at(uniqueKey);
	
	//create 5 new incStats for the new stream

	const float lambdas[] = { 0.01,0.1,1,3,5 };
	std::vector<IncStats>* vec;

	//#TODO: check if this if statement is neccessary (might be not)
	if (this->_incStatsCollection.find(uniqueKey) != this->_incStatsCollection.end())
	{
		vec = this->_incStatsCollection.at(uniqueKey);
	}
	else
	{
		for (size_t i = 0; i < 5; i++)
		{
			vec->push_back(IncStats(uniqueKey, lambdas[i]));
		}
		this->_incStatsCollection.insert({ uniqueKey,*vec });
	}

	return vec;
}

/*
This function adds a new relative Inc stats to the main vector
Input: the keys of the two streams
Output: pointer to the vector of relative inc stats (with different lambda in each index)
Throw: std::exception
*/

vector<RelativeIncStats>* IncStatsData::registerRelatedStreams(string firstUniqueKey, string secondUniqueKey) throw()
{
	const float lambdas[] = { 0.01,0.1,1,3,5 };
	string uniqueKey = firstUniqueKey + '+' + secondUniqueKey;
	vector<RelativeIncStats>* vec;
	std::vector<IncStats>* pFirstGroup = this->registerStream(firstUniqueKey);
	std::vector<IncStats>* pSecondGroup = this->registerStream(secondUniqueKey);

	if (this->isRelStreamExists(uniqueKey))
	{
		return this->_relIncStatsCollection.at(uniqueKey);
	}

	//create new relative incremental statistics

	for (int i = 0 ; i < 5 ; i++) // for each lambda
	{
		IncStats* pFirst = &((*pFirstGroup)[i]);
		IncStats* pSecond = &((*pSecondGroup)[i]);

		vec->push_back(RelativeIncStats(pFirst, pSecond)));
	}
	
	this->_relIncStatsCollection.insert({uniqueKey, *vec});

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
void IncStatsData::insertPacket(string firstKey, float value, Time timestamp) throw()
{
    if (!this->isStreamExists(firstKey))
        this->registerStream(firstKey);

    for (int i = 0; i <this->_incStatsCollection[firstKey].size() ; ++i) // for each lambda
    {
        this->insertPacket(firstKey,value,timestamp,i);
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

*/
void IncStatsData::insertPacket(string key, Time timestamp) throw()
{
    if (!this->isStreamExists(key))
        this->registerStream(key);

    for (int i = 0; i <this->_incStatsCollection[key].size() ; ++i)
    {
        this->_incStatsCollection[key][i].insertElement(timestamp);
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
 This function gets stats of two specific streams of all lambdas
 Input: key - The stream key : std::string
 Output: all stats of stream : vector<float>
 Throw: std::exception
*/
vector<float> IncStatsData::getStatsTwoDimensions(string firstKey, string secondKey) const throw()
{
	string uniqueKey = firstKey + '+' + secondKey;
	if (!this->isRelStreamExists(uniqueKey))
	{
		throw std::exception("the required link doesn't exist");
	}
	
	vector<float> result;
	for (size_t i = 0; i < this->_relIncStatsCollection.at(key).size() ; i++)
	{
		vector<float> val = this->_relIncStatsCollection.at(key)[i].getRelativeStats();
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

/*
The function will check if an instance of RelativeIncStats that refers to 2 specific streams is already exist, and return it if exist
input: instance of RelativeIncStats
output: a pointer to the exist link or nullptr
*/
RelativeIncStats* IncStatsData::getExistLink(RelativeIncStats& link)
{
	for (int i = 0; i< this->_relIncStatsCollection.size(); i++)
	{
		if(link == this->_relIncStatsCollection[i])
		{
			return &(this->_relIncStatsCollection[i]);
		}
	}

	return nullptr;
}