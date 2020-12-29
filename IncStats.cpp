#include "IncStats.h"

#include <math.h>


//--------constructor----------
IncStats::IncStats(float decayFactor)
{
    this->_decayFactor = decayFactor;
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
    int diff = timeStamp - this->_timeStamp;
    float decay = pow(2,-1*this->_decayFactor *  diff );
    this->_weight *= decay;
    this->_linearSum *= decay;
    this->_squaredSum *= decay;
}








