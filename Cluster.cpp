//
// Created by ofir on 09/01/2021.
//

#include "Cluster.h"

//Constructors
Cluster::Cluster(Cluster *left, Cluster *right, float height, vector<vector<float>> * distance)
{
    this->_height = height;

    this->_left = left;
    this->_right = right;

    this->_ids = left->_ids;
    this->_ids.insert(this->_ids.end(),right->_ids.begin(),right->_ids.end());

    this->_distance = distance;


}

Cluster::Cluster(int id,vector<vector<float>>* distance)
{
    this->_ids.push_back(id);

    this->_height = 0;

    this->_right = nullptr;
    this->_left = nullptr;

    this->_distance = distance;
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
float Cluster::calcDistance(Cluster other) const {
    //distance between 2 clusters calculated with average
    float sum = 0;
    for (int i = 0; i < other.getSize(); ++i) {
        for (int j = 0; j < other.getSize(); ++j) {
            sum += (*(this->_distance))[i][j];
        }
    }
    return sum / (float) (this->getSize() * other.getSize());
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

