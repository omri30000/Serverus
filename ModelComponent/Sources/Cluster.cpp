//
// Created by ofir on 09/01/2021.
//

#include "../Headers/Cluster.h"
#include <algorithm>
#include <math.h>
#include <iostream>

using std::min;
using std::max;
//Constructors
Cluster::Cluster(Cluster *left, Cluster *right, float height)
{
    this->_height = height;

    this->_left = left;
    this->_right = right;

    this->_ids = left->_ids;
    this->_ids.insert(this->_ids.end(),right->_ids.begin(),right->_ids.end());



}

Cluster::Cluster(int id)
{
    this->_ids.push_back(id);

    this->_height = 0;

    this->_right = nullptr;
    this->_left = nullptr;
}
//Destructor - also free from memory
Cluster::~Cluster()
{
    if(_right != nullptr)
        delete _right;
    if(_left != nullptr)
        delete _left;
}
/*
 This function calculates the distance between 2 clusters
 Input:other : The second cluster : Cluster
 Output: The distance : float
 */
float Cluster::calcDistance(const Cluster& other,const vector<vector<float>>& distanceMatrix) const {
    //distance between 2 clusters calculated with average
    float sum = 0;
    for (int i = 0; i < this->getSize(); ++i) {
        int this_id = this->_ids[i];
        for (int j = 0; j < other.getSize(); ++j) {
            int other_id = other._ids[j];
            //using min() and max() because distance matrix is a triangle
            sum += distanceMatrix[std::max(this_id,other_id)][std::min(this_id,other_id)];

        }
    }
    float res = sum / (float) (this->getSize() * other.getSize());
    if(std::isnan(res))
        std::cout<<"fuck";
    return res;
}


//getters
int Cluster::getSize() const
{
    return _ids.size();
}

float Cluster::getHeight() const
{
    return _height;
}

vector<int> Cluster::getIds() const {
    return this->_ids;
}

Cluster *Cluster::getLeft() const {
    return _left;
}

Cluster *Cluster::getRight() const {
    return _right;
}



/*
int Cluster::getSize() const
{
    int right =0;
    int left = 0;
    if(this->_right != nullptr)
        right = this->_right->getSize();
    if(this->_left != nullptr)
        left = this->_left->getSize();

    return left + right +1;
}*/

