//
// Created by ofir on 25/01/2021.
//

#include "Neuron.h"
#include <cstdlib>
#include <ctime>

Neuron::Neuron(int previousLength)
{
    srand(time(NULL)); // it's better to do in main
    _weights = std::valarray<float>(previousLength);

    for (int i = 0; i < previousLength; ++i)
    {
        _weights[i] = rand()%10;
    }
}

Neuron::Neuron(valarray<float> weights)
{
    _weights = weights;
}
//initial with in a specific range random values
Neuron::Neuron(pair<float, float> range, int previousLength)
{
    srand(time(NULL));
    _weights =std::valarray<float>(previousLength);
    for (int i = 0; i < _weights.size(); ++i)
    {
        float val = rand() / (float)RAND_MAX;
        _weights[i] =  range.first +val*(range.second - range.first);
    }
}
/*
 This function calculates the neuron value to a vector
 Input: values of previous layer
 Output:Neuron Value
 */
float Neuron::feedForward(valarray<float> vals)
{
    return (vals * _weights).sum();
    //add activation function  + bias optional
}

