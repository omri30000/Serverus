#include "RelativeIncStats.h"

#include <math.h>

RelativeIncStats::RelativeIncStats(IncStats* first, IncStats* second)
{
    this->_firstIncStats = first;
    this->_secondIncStats = second;

    this->_firstCurrResidule = 0;
    this->_secondCurrResidule = 0;

    this->_sumResiduleProducts = 0;
    this->_currWeight = 0.00000000000000000001;  // very small number but not zero
}

RelativeIncStats::RelativeIncStats(IncStats* first, IncStats* second, Time initialTime) : _currTimeStamp(initialTime)
{
    this->_firstIncStats = first;
    this->_secondIncStats = second;

    this->_firstCurrResidule = 0;
    this->_secondCurrResidule = 0;

    this->_sumResiduleProducts = 0;
    this->_currWeight = 0.00000000000000000001; // very small number but not zero
}

/*
the function will update a relative inc stats
input: the ID of the stream that should be updated, the produced elements (the new value and the timestamp)
output: none
*/
void RelativeIncStats::update(string iSID, float newValue, Time timeStamp)
{
    float newResidule = 0, temp = 0;

    if (iSID == this->_firstIncStats->getIdentifier())
    {
        this->_secondIncStats->performDecay(timeStamp);
        this->performDecay(timeStamp, 1);

        this->_firstCurrResidule = (newValue - this->_firstIncStats->calcMean());

        newResidule = (this->_firstCurrResidule * this->_secondCurrResidule);

        this->_sumResiduleProducts += newResidule;
        this->_currWeight += 1;
    }
    else if (iSID == this->_secondIncStats->getIdentifier())
    {
        this->_firstIncStats->performDecay(timeStamp);
        this->performDecay(timeStamp, 2);

        this->_secondCurrResidule = (newValue - this->_secondIncStats->calcMean());

        newResidule = (this->_secondCurrResidule * this->_firstCurrResidule);
        
        this->_sumResiduleProducts += newResidule;
        this->_currWeight += 1;
    }
    else{
        throw std::exception();
    }
}

/*
This function processes the decay function
Input: 
        * timeStamp : The time of the instance : Time
        * index : determine which incStats shold be used (1/2) : int
Output:None
*/
void RelativeIncStats::performDecay(Time timeStamp, int index)
{
    long timeDifference = timeStamp - this->_currTimeStamp;
    float factor = 0;
    
    /*std::cout << "****" << std::endl;
    std::cout << timeStamp.toString() << std::endl;
    std::cout << this->_currTimeStamp.toString() << std::endl;
    std::cout << timeDifference << std::endl;
    std::cout << "****" << std::endl;*/

    if (timeDifference > 0)
    {
        switch (index)
        {
            case 1:
                factor = pow(2, -1 *(this->_firstIncStats->getDecayFactor() * timeDifference));
                /*std::cout << "--1--" << std::endl;
                std::cout << factor << std::endl;
                std::cout << "--1--" << std::endl;*/
                this->_sumResiduleProducts *= factor;
                this->_currWeight *= factor;
                this->_firstCurrResidule *= factor;
                break;
            case 2:
                factor = pow(2, -1 *(this->_secondIncStats->getDecayFactor() * timeDifference));
                /*std::cout << "--2--" << std::endl;
                std::cout << factor << std::endl;
                std::cout << "--2--" << std::endl;*/
                this->_sumResiduleProducts *= factor;
                this->_currWeight *= factor;
                this->_secondCurrResidule *= factor;
                break;
            default:
                throw std::exception();
                break;
        } 
        this->_currTimeStamp = timeStamp;
    }
}

/*
The method will put the 2D statistics of the inc stats into a vector of statistics
input: none
output: vector of statistics
*/
vector<float> RelativeIncStats::getRelativeStats() const
{
    vector<float> vec;

    vec.push_back(this->calcCovariance());
    vec.push_back(this->calcCorrelationCoefficiency());
    /*std::cout << "====" << std::endl;
    std::cout << this->calcCovariance() << std::endl;
    std::cout << this->calcCorrelationCoefficiency() << std::endl;
    std::cout << "====" << std::endl;*/
    vec.push_back(this->_firstIncStats->calcRadius(*this->_secondIncStats));
    vec.push_back(this->_firstIncStats->calcMagnitude(*this->_secondIncStats));

    return vec;
}

/*
the function will calculate the covariance approximation of the 2 inc stats of the class
input: none
output: covariance approximation
*/
float RelativeIncStats::calcCovariance() const
{

    /*std::cout << "????" << std::endl;
    std::cout << this->_sumResiduleProducts << std::endl;
    std::cout << this->_currWeight << std::endl;
    std::cout << "????" << std::endl;*/
    return this->_sumResiduleProducts / this->_currWeight;
}

/*
the function will calculate the correlation coefficiency of 2 inc stats 
input: none
output: correlation coefficiency of 2 inc stats 
*/
float RelativeIncStats::calcCorrelationCoefficiency() const
{
    float stdProduct = this->_firstIncStats->calcStandardDeviation() * this->_secondIncStats->calcStandardDeviation();

    return (stdProduct != 0) ? this->calcCovariance() / stdProduct : 0; 
}

/*

*//*
bool RelativeIncStats::operator==(const RelativeIncStats& other) const
{
    return (*(this->_firstIncStats) == (*other._firstIncStats)) && (*(this->_secondIncStats) == *(other._secondIncStats));
}*/