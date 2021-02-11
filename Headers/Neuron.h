//
// Created by ofir on 25/01/2021.
#pragma once

#include <valarray>
#include <map>
using std::valarray;
using std::pair;
class Neuron
{
protected:
    valarray<float> _weights;
public:
    Neuron(int previousLength);
    Neuron(valarray<float> weights);
    Neuron (pair<float,float> range,int previousLength);
    float feedForward(valarray<float> vals);
    //setters
    //getters

};


