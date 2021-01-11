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
    vector<vector<float>> calcCurrentDistanceMatrix(vector<Cluster*> vec);

    static pair<pair<int,int>,float> findMin(vector<vector<float>> vec);

    void cutDendrogram(Cluster* cluster,vector<Cluster*> *vec) const;


public:
    FeatureMapper(int learningLimit, int m,int statsSize);
    void update(vector<float> stats);
    pair<vector<vector<int>>, int> cluster();
    bool getState() const;


};