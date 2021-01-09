//
// Created by ofir on 09/01/2021.
//

#pragma  once

#include <vector>
#include <pair>
#include "Cluster.h"
using std::vector;
using std::pair;

class FeatureMapper
{
protected:
    vector<float> _c;
    vector<float> _cr;
    vector<float> _crs;

    int _m;
    int _learningLimit;

    vector<vector<float>> _correlation;
    vector<vector<float>> calcInitialDistanceMatrix() const;
    vector<vector<float>> calcCurrentDistanceMatrix(vector<Cluster*> vec);
    pair<pair<int,int>,int> findMin(vector<vector<float>> vec);

    void cutDendrogram(Cluster* cluster,vector<Cluster*> *vec) const;


public:
    FeatureMapper(int learningLimit, int m,int statsSize);
    void update(vector<float> stats);
    pair<vector<vector<int>>, int> cluster();


};