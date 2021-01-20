#include "IncStats.h"

#include <math.h>


//--------constructor----------
IncStats::IncStats(string id, float decayFactor)
{
    this-> _identifier = id;
    this->_decayFactor = decayFactor;
    this->_weight = 0.00000000000000000001;  // very small number but not zero
    this->_linearSum = 0;
    this->_squaredSum = 0;
    this->_mean = 0;
    this->_standardDeviation = 0;
}

/*
This function inserts a new element to the stream, and updates statistics
Input:
    element: Element value : float
    timeStamp: The time the new element arrived : Time
Output: None
*/
void IncStats::insertElement(float element, Time timeStamp)
{
    this->performDecay(timeStamp);
    this->_weight += 1;
    this->_linearSum += element;
    this->_squaredSum += element*element;
    this->_timeStamp = timeStamp;

    //perform stats
    this->calcMean();
    this->calcStandardDeviation();
}

/*
This function processes the decay function on each one of the IncStats Elements
Input: timeStamp : The time of the instance : Time
Output:None
*/

void IncStats::performDecay(Time timeStamp)
{
    long diff = timeStamp - this->_timeStamp;
    //std::cout << "dif --> " << diff << std::endl;
    float decay = pow(2,-1*this->_decayFactor *  diff );
    this->_weight *= decay;
    this->_linearSum *= decay;
    this->_squaredSum *= decay;
}

/*
This function returns all stats
Input:None
Output:Stream stats : vector<float>
*/
vector<float> IncStats::getStats() const
{
    return std::vector<float>{this->_weight, this->_mean, this->_standardDeviation};
}

//options to move to static function
/*
This function calculates Mean value
Input:None
Output:None / Mean value : float
*/
float IncStats::calcMean()
{
    float tmp = this->_linearSum / this->_weight;
    if (!isnan(tmp))
        this->_mean = tmp;
    return this->_mean;
}

/*
This function calculates Standard Deviation value
Input:None
Output:None / Standard Deviation value : float
*/
float IncStats::calcStandardDeviation()
{
    float tmp = sqrt(abs(this->_squaredSum / this->_weight - pow(this->_linearSum / this->_weight, 2)));
    if (!isnan(tmp))
        this->_standardDeviation = tmp;
    return this->_standardDeviation;
}

/*
The function will calc the magnitude between the current IncStats and the other (in param)
input: other IncStats used for calculations
output: the magnitude of those 2 Inc stats
*/
float IncStats::calcMagnitude(IncStats other)
{
    return sqrt(pow(this->calcMean(), 2) + pow(other.calcMean(), 2));
}

/*
The function will calc the radius between the current IncStats and the other (in param)
input: other IncStats used for calculations
output: the radius of those 2 Inc stats
*/
float IncStats::calcRadius(IncStats other)
{
    return sqrt(pow(this->calcStandardDeviation(), 4) + pow(other.calcStandardDeviation(), 4));
}

void IncStats::insertElement(Time timeStamp) {
    insertElement(timeStamp - this->_timeStamp,timeStamp);
}

/*

*/
string IncStats::getIdentifier() const
{
    return this->_identifier;
}

/*

*/
float IncStats::getDecayFactor() const
{
    return this->_decayFactor;
}