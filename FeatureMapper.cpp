//
// Created by ofir on 09/01/2021.
//

#include "FeatureMapper.h"
#include <math.h>

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
        this->_correlation.push_back(vector<float>(statsSize,0));
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

/*
    This function
 */
vector<vector<float>> FeatureMapper::calcDistanceMatrix() const {
    vector<vector<float>> res;
    for (int i = 0; i < this->_correlation.size(); ++i)
    {
        res.push_back(vector<float>(_correlation.size(),0));
        for (int j = 0; j < _correlation.size(); ++j)
        {
            res[i][j] = 1 - _correlation[i][j]/(sqrt(_crs[i]) * sqrt(_crs[j]));
        }
    }
    return res;
}
/*
void func(void)
{
    vector<Element*> vec;

    while(vec.size()!= 1) {
        //build Distance

        //find two minimum - merge
    }
    vector<Element*> cut;
    //if not cut
    cut_tree(vec[0],&cut,m);
}

void cut_tree(Cluster* cluster,vector<Element*> *vec,int m)
{
    if(cluster->getSize() <= m)
        vec->push_back(cluster);
    else
    {
        cut_tree(cluster.getLeft(),vec,m);
        cut_tree(cluster.getRight(),vec,m);

    }
}

*/