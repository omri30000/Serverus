//
// Created by ofir on 09/01/2021.
//

#pragma  once

#include <vector>
#include <utility>
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
    int _cursor;

    vector<vector<float>> _correlation;
    vector<vector<float>> _initialDistanceMatrix;

    void calcInitialDistanceMatrix();
    void calcCurrentDistanceMatrix(vector<Cluster*> vec,vector<vector<float>>& distanceMatrix,pair<int,int> changedIndexes);

    static pair<pair<int,int>,float> findMin(vector<vector<float>> vec);

    void cutDendrogram(Cluster* cluster,vector<Cluster*> *vec) const;


public:
    FeatureMapper(int learningLimit, int m,int statsSize);
    void update(vector<float> stats);
    vector<vector<int>> cluster();
    bool getState() const;


};