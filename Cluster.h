//
// Created by ofir on 09/01/2021.
//

#pragma once

#include <vector>

using std::vector;

class Cluster {
protected:

    float _height;

    vector<int> _ids; //for saving time only - can be ignored

    Cluster* _right;
    Cluster* _left;



public:
    Cluster(Cluster* left, Cluster * right, float height); //for merging between 2 clusters
    Cluster(int id); // for initial data type

    ~Cluster();
    int getSize() const;
    float getHeight() const;
    Cluster * getLeft() const;
    Cluster * getRight() const;
    vector<int> getIds() const;
    float calcDistance(const Cluster& other,const vector<vector<float>>& distanceMatrix) const;
};


