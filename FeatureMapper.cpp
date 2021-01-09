//
// Created by ofir on 09/01/2021.
//

#include "FeatureMapper.h"

//constructor
FeatureMapper::FeatureMapper(int learningLimit, int m,int statsSize) {

    this->_learningLimit;
    this->_m = m;

    this->_cursor;
    this->_c = vector<float>(statsSize,0);
    this->_cr = vector<float>(statsSize,0);
    this->_crs = vector<float>(statsSize,0);

    for (int i = 0; i < statsSize; ++i)
    {
        this->_correlation[i] = vector<float>(statsSize,0);
    }
}

/*
 This function updates new stats in FM
 Input: stats : The new stats from FE : float
 Output : None
 */
void FeatureMapper::update(vector<float> stats) 
{
    this->_cursor++;
    vector<float> _crTime(stats.size(),0);
    for (int i = 0; i < stats.size(); i++) {

        this->_c[i] += stats[i];
        _crTime[i] = stats[i] - this->_c[i] / (float) _cursor;
        this->_cr[i] += _crTime[i];
        this->_crs[i] += _crTime[i] * _crTime[i]; //pow(val,2)
    }
    //updates Correlation matrix
    for (int i = 0; i < stats.size(); i++) {
        for (int j = 0; j <stats.size() ; j++) {
            this->_correlation[i][j] += _crTime[i] * _crTime[j];
        }
    }
}

