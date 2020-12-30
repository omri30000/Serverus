//
// Created by ofir on 30/12///

#include "FeatureExtractor.h"

//constructors
FeatureExtractor::FeatureExtractor() : FeatureExtractor(FeatureExtractor::DEFAULT_LAMBDAS)
{
}

FeatureExtractor::FeatureExtractor(vector<float> lambdas)
{
    this->_lambdas = lambdas;
}













