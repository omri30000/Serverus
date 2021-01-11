//
// Created by ofir on 09/01/2021.
//

#include "FeatureMapper.h"
#include <cmath>

//constructor
FeatureMapper::FeatureMapper(int learningLimit, int m,int statsSize) {

    this->_cursor = 0;
    this->_learningLimit = learningLimit;
    this->_m = m;

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
    vector<float> crTime(stats.size(),0);
    for (int i = 0; i < stats.size(); i++) {

        this->_c[i] += stats[i];
        crTime[i] = stats[i] - this->_c[i] / (float) _cursor;
        this->_cr[i] += crTime[i];
        this->_crs[i] += crTime[i] * crTime[i]; //pow(val,2)
    }
    //updates Correlation matrix
    for (int i = 0; i < stats.size(); i++) {
        for (int j = 0; j <stats.size() ; j++) {
            this->_correlation[i][j] += crTime[i] * crTime[j];
        }
    }
}

/*
This function calculates the initial Distance matrix - between points and not clusters
Input: None
Output: distance matrix : vector<vector<float>>
 */
void FeatureMapper::calcInitialDistanceMatrix()
{

    for (int i = 0; i < this->_correlation.size(); ++i)
    {
        this->_initialDistanceMatrix.push_back(vector<float>(i+1,0));
        for (int j = 0; j < i+1; ++j)
        {
            _initialDistanceMatrix[i][j] = 1 - (_correlation[i][j]/(sqrt(_crs[i]) * sqrt(_crs[j])));
        }
    }
    int a = 0;
}

/*
  This function calculates and returns the current distance matrix
  Input: vec : The current clusters : vector<Cluster*>
  Output:The current distance matrix : vector<vector<float>>
 */
vector<vector<float>> FeatureMapper::calcCurrentDistanceMatrix(vector<Cluster*> vec)
{
    vector<vector<float>> res;
    for (int i = 0; i < vec.size(); ++i)
    {
        res.push_back(vector<float>(i+1,0));
        for (int j = 0; j < i+1; ++j)
        {
            res[i][j] = vec[i]->calcDistance(*vec[j],_initialDistanceMatrix);
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

    for (int i = 0; i < _c.size(); ++i) {
        vec.push_back(new Cluster(i));
    }
    calcInitialDistanceMatrix();
    vector<vector<float>> currDistance;// = _initialDistanceMatrix;
    while(vec.size()!= 1)
    {
        currDistance = this->calcCurrentDistanceMatrix(vec);
        pair<pair<int,int>,int> indexes = FeatureMapper::findMin(currDistance);
        //if(indexes.second == -1)
        //    continue;
        vec[indexes.first.second] = new Cluster(vec[indexes.first.first],vec[indexes.first.second],indexes.second);
        vec.erase(vec.begin() + indexes.first.first);
        //find two minimum - merge
    }

    vector<Cluster*> cut;
    cutDendrogram(vec[0],&cut);
    //

    vector<vector<int>> mapping;
    for (int i = 0; i < cut.size(); ++i) {
        mapping.push_back(cut[i]->getIds());
    }

    return {mapping,mapping.size()};
}
/*
 This function cuts a Dendrogram to clusters which each cluster's size lower than m
 Input:
        cluster - pointer to the head od Dendrogram (biggest cluster) :Cluster*
        vec - pointer to vector where there all chosen clusters will be added : vector<Cluster*>
Output:None
 */
void FeatureMapper::cutDendrogram(Cluster* cluster,vector<Cluster*> *vec) const
{
    if(cluster->getSize() <= _m)
        vec->push_back(cluster);
    else
    {
        cutDendrogram(cluster->getLeft(),vec);
        cutDendrogram(cluster->getRight(),vec);
    }
}

/*
 This function finds the 2 closest clusters indexes and their distance value
 Input: vec: The distance matrix
 Output: The indexes of the closest clusters, their distance : std::pair<std::pair<int,int>,float>
 */
pair<pair<int, int>, float> FeatureMapper::findMin(vector<vector<float>> vec) {
    pair<int,int> p = {-1,-1};
    float min = -1;
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j)
        {
            if( i == j)
                continue;
            if(vec[i][j] > 0 && (min == -1  || vec[i][j] < min ))
            {
                min = vec[i][j];
                p ={i,j};
            }
        }
    }
    if( p == std::pair<int,int>(-1,-1))
        p = p;

    return {p,min};
}
/*
    This function returns if the first part of the FeatureMapper Process has been finished
    Input:None
    Output:If the first part has been finished : bool
 */
bool FeatureMapper::getState() const{
    return _cursor >=_learningLimit;
}
