#include "../Headers/RelativeIncStats.h"

#include <math.h>

RelativeIncStats::RelativeIncStats(IncStats* first, IncStats* second)
{
    this->_arr[0] = first;
    this->_arr[1] = second;

    this->_residules[0] = 0;
    this->_residules[1] = 0;

    this->_sumResiduleProducts = 0;
    this->_currWeight = 0.00000000000000000001;  // very small number but not zero
}

RelativeIncStats::RelativeIncStats(IncStats* first, IncStats* second, Time initialTime) : _currTimeStamp(initialTime)
{

    this->_arr[0] = first;
    this->_arr[1] = second;

    this->_residules[0] = 0;
    this->_residules[1] = 0;

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


    int id = this->_arr[1]->getIdentifier() == iSID;

    if(!id && iSID != this->_arr[0]->getIdentifier())
        throw std::exception();

    this->_arr[!id]->performDecay(timeStamp);
    this->performDecay(timeStamp,id);

    this->_residules[id] = (newValue - this->_arr[id]->calcMean());
    newResidule = this->_residules[id] * this->_residules[!id];
    this->_sumResiduleProducts += newResidule;

    this->_currWeight+=1;
    return;

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

    if (timeDifference > 0)
    {
        if(index <0 || index >1)
            throw std::exception();

        factor = pow(2,-1*(this->_arr[index]->getDecayFactor() * (float)timeDifference));
        this->_sumResiduleProducts *= factor;
        this->_currWeight *= factor;
        this->_residules[index] *= factor;

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
    vec.push_back(this->_arr[0]->calcRadius(*this->_arr[1]));
    vec.push_back(this->_arr[0]->calcMagnitude(*this->_arr[1]));


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
    float stdProduct = this->_arr[0]->calcStandardDeviation() * this->_arr[1]->calcStandardDeviation();
    return (stdProduct != 0) ? this->calcCovariance() / stdProduct : 0; 
}

/*

*//*
bool RelativeIncStats::operator==(const RelativeIncStats& other) const
{
    return (*(this->_firstIncStats) == (*other._firstIncStats)) && (*(this->_secondIncStats) == *(other._secondIncStats));
}*/