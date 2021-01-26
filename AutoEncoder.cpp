//
// Created by ofir on 25/01/2021.
//

#include "AutoEncoder.h"

AutoEncoder::AutoEncoder(int inputSize)
{
    float b = 0.75;
    pair<float,float> range = {-1/inputSize,1/inputSize};
    this->_layers = vector<vector<Neuron>>(2);
    for (int i = 0; i <_layers.size(); ++i)
    {
        for (int j = 0; j < inputSize; ++j)
        {
            _layers[i].push_back(Neuron(range,inputSize));
        }
        inputSize *= b;

    }
    //TODO:fix this
    _learningRate = 1;// for now only
}

valarray<float> AutoEncoder::feedForward(valarray<float> input) {
    std::valarray<float> res = input;
    for (int i = 0; i < _layers.size(); ++i)
    {
        valarray<float> tmp = res;
        res = valarray<float>(_layers[i].size());
        for (int j = 0; j < _layers[i].size(); ++j)
        {
            res[j] = _layers[i][j].feedForward(tmp);
        }
    }
    return res;
}

/*
 This function calculates the RMSE value for an input
 Input: input to the AE : valarray<float>
 Output: The RMSE value
 */
float AutoEncoder::calcRmse(valarray<float> input) {
    return std::pow(feedForward(input) - input,2).sum();
}

