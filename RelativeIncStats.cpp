#include "RelativeIncStats.h"

RelativeIncStats::RelativeIncStats(IncStats* first, IncStats* second)
{
    this->_firstIncStats = first;
    this->_secondIncStats = second;

    this->_sumResiduleProducts = 0;
    this->_currWeight = 0.000000001; // very small number but not zero
}

/*
the function will calculate the covariance approximation of the 2 inc stats of the class
input: none
output: covariance approximation
*/
float RelativeIncStats::calcCovariance()
{
    return this->_sumResiduleProducts / this->_currWeight;
}

/*
the function will calculate the correlation coefficiency of 2 inc stats 
input: none
output: correlation coefficiency of 2 inc stats 
*/
float RelativeIncStats::calcCorrelationCoefficiency()
{
    float stdProduct = this->_firstIncStats->calcStandardDeviation() * this->_secondIncStats->calcStandardDeviation();

    return (stdProduct != 0) ? this->calcCovariance() / stdProduct : 0; 
}