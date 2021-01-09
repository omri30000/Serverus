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
This function calculates the initial Distance matrix - between points and not clusters
Input: None
Output: distance matrix : vector<vector<float>>
 */
vector<vector<float>> FeatureMapper::calcInitialDistanceMatrix() const {
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
 This function performs clustering on the data
 Input: None
 Output: The mapping of the data, k - number of AE/clusters : pair<vector<vector<int>>, int>
 */
pair<vector<vector<int>>, int> FeatureMapper::cluster() {

    vector<Cluster*> vec;
    vector<vector<float>> initDistance= this->calcInitialDistanceMatrix();

    for (int i = 0; i < _c.size(); ++i) {
        vec.push_back(new Cluster(i,&initDistance));
    }

    vector<vector<float>> currDistance = this->calcCurrentDistanceMatrix(vec);
    while(vec.size()!= 1)
    {
        currDistance = this->calcCurrentDistanceMatrix(vec);
        pair<pair<int,int>,int> indexes = FeatureMapper::findMin(currDistance);

        vec[indexes.first.first] = new Cluster(vec[indexes.first.first],vec[indexes.first.second],indexes.second,&initDistance);
        vec.erase(vec.begin() + indexes.first.second);
        //find two minimum - merge
    }

    vector<Cluster*> cut;
    cutDendogram(vec[0],&cut);
    //

    vector<vector<int>> mapping;
    for (int i = 0; i < cut.size(); ++i) {
        mapping.push_back(cut[0]->getIds());
    }

    return {mapping,vec.size()};
}
/*
 This function cuts a Dendogram to clusters which each cluster's size lower than m
 Input:
        cluster - pointer to the head od Dendogram (biggest cluster) :Cluster*
        vec - pointer to vector where there all chosen clusters will be added : vector<Cluster*>
Output:None
 */
void FeatureMapper::cutDendogram(Cluster* cluster,vector<Cluster*> *vec) const
{
    if(cluster->getSize() <= _m)
        vec->push_back(cluster);
    else
    {
        cutDendogram(cluster->getLeft(),vec);
        cutDendogram(cluster->getRight(),vec);
    }
}
/*
  This function calculates and returns the current distance metrix
  Input: vec : The current clusters : vector<Cluster*>
  Output:The current distance matrix : vector<vector<float>>
 */
vector<vector<float>> FeatureMapper::calcCurrentDistanceMatrix(vector<Cluster*> vec)
{
    vector<vector<float>> res;
    for (int i = 0; i < vec.size(); ++i) {
        res.push_back(vector<float>());
        for (int j = 0; j < i+1; ++j) {
            res[i][j] = vec[i]->calcDistance(*vec[j]);
        }
    }
    return res;
}
/*
 This function finds the 2 closest clusters indexes and their distance value
 Input: vec: The distance matrix
 Output: The indexes of the closest clusters, their distance : std::pair<std::pair<int,int>,int>
 */
pair<pair<int, int>, int> FeatureMapper::findMin(vector<vector<float>> vec) {
    pair<int,int> p = {-1,-1};
    int min = -1;
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            if( min == -1 || vec[i][j] < min )
            {
                min = vec[i][j];
                p ={i,j};
            }
        }
    }
    return {p,min};
}
