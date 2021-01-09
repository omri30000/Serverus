//
// Created by ofir on 09/01/2021.
//

#pragma once

#include <vector>

using std::vector;

class Cluster {
protected:

    int _height;

    vector<float> _ids; //for saving time only - can be ignored

    Cluster* _right;
    Cluster* _left;

    vector<vector<float>>* _distance; // between all initial data points



public:
    Cluster(Cluster* left, Cluster * right, float height,vector<vector<float>>* distance); //for merging between 2 clusters
    Cluster(int id,vector<vector<float>>* distance); // for initial data type

    int getSize() const;
    float getHeight() const;

    float calcDistance(Cluster other) const;
};


