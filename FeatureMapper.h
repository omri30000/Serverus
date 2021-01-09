//
// Created by ofir on 09/01/2021.
//
#pragma once

#include <vector>

using std::vector;
class FeatureMapper
{
protected:
    vector<float> _c;
    vector<float> _cr;
    vector<float> _crs;
    vector<vector<float>> _correlation;
    //distance - matrix

    int _cursor;
    int _learningLimit;
    int _m;

    vector<vector<float>> calcDistanceMatrix() const;
public:
    FeatureMapper( int learningLimit  ,int m ,int statsSize);
    void update(vector<float> stats);
    //cluster
    //getstate


};


