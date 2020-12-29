#include "IncStatsData.h"

//constructor
IncStatsData::IncStatsData()
{

}


void IncStatsData::registerStream(string uniqueKey) throw()
{
	//check if not exists
	if(this->isStreamExists(uniqueKey)
		throw "problem";
	

	const float lambdas[] = { 0.01,0.1,1,3,5 };
	std::vector<uniqueKey> vec;
	for (size_t i = 0; i <5; i++)
	{
		vec.push_back(IncStats(lambdas[i]));
	}
	this->_incStatsCollection.insert({ uniqueKey,vec });

}

void IncStatsData::insertPacket(string key, float value, Time timestamp, int lambdaindex) throw()
{
	if (!this->isStreamExists(key))
		throw "problem";

	this->_incStatsCollection[key][lambdaindex].insertElement(value, timestamp);
}

vector<float> IncStatsData::getStats(string key) const throw()
{
	if (!this->isStreamExists(key))
		throw "problem";
	vector<float> result;
	for (size_t i = 0; i < this->_incStatsCollection[key].size ; i++)
	{
		vector<float> val = this->_incStatsCollection[key][i].getStats();
		for (float stat : val)
		{
			result.push_back(stat);
		}

	}
	retuen result;
}

bool IncStatsData::isStreamExists(string key) const
{
	try
	{
		this->_incStatsCollection.at(key);
	}
	catch (Exception e)
	{
		return false;
	}
	return true;
}
