//
// Created by ofir on 25/01/2021.
//

#include <vector>
#include "Neuron.h"

using std::vector;


class AutoEncoder
{
protected:
    vector<vector<Neuron>> _layers;
    float _learningRate;

public:
    AutoEncoder(int inputSize);
    valarray<float> feedForward(valarray<float> input);
    float calcRmse(valarray<float> input);
};



