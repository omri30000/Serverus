//
// Created by ofir on 25/01/2021.
//

#include "AutoEncoder.h"

//constructor
AutoEncoder::AutoEncoder(int inputSize,float learningRate = 1.0)
{
    _inputSize = inputSize;
    float b = 0.75;

    double a = 1.0/inputSize;

    _weights = valarray<valarray<float>>(_inputSize*b);
    for (int i = 0; i < _weights.size(); ++i)
    {
        _weights[i] = valarray<float>((double)0, _inputSize);
        for (int j = 0; j <_weights[i].size() ; ++j)
        {
            _weights[i][j] = uniform({-a,a});
        }
    }
    _hiddenBias = valarray<float>((double)0,_inputSize*b);
    _visibleBias = valarray<float>((double)0,_inputSize);



    _learningRate = learningRate;// for now only
}

/*
 This function calculates the RMSE value for an input
 Input: input to the AE : valarray<float>
 Output: The RMSE value
 */
float AutoEncoder::feedForward(valarray<float> input)
{

    std::valarray<float> res(_inputSize);
    std::valarray<float> hidden(_weights.size());

    getHiddenLayer(input,hidden);
    getVisibleLayer(hidden,res);

    return calcRmse(input,res);
}

/*
 This function calculates the RMSE value between 2 tensors
 Input:
        input: input of the AE : valarray<float>
        reconstruct: input of the AE : valarray<float>
 Output: The RMSE value
 */
float AutoEncoder::calcRmse(valarray<float> input,valarray<float> reconstruct) {
    return std::pow(input- reconstruct,2).sum();
}
/*
 This function returns the Hidden Layer - The second layer (feed forward)
 Input:vals : the input to the AE
       res: refrence to the hidden layer values
  Output :None
 */
void AutoEncoder::getHiddenLayer(valarray<float> vals, valarray<float> &res)
{
    for (int i = 0; i < _weights.size(); ++i)
    {
        res[i] = (vals * _weights[i]).sum();
    }
    //hidden.apply(sigmoid);
    res += _hiddenBias;
}
/*
 This function returns the Visible Layer - The third layer (feed forward)
 Input:vals : the input to the AE
       res: refrence to the visible layer values
  Output :None
 */
void AutoEncoder::getVisibleLayer(valarray<float> vals, valarray<float> &res)
{
    for (int i = 0; i < _inputSize; ++i)
    {
        res[i] = 0;
        for (int j = 0; j < _weights.size(); ++j)
        {
            res[i] += _weights[j][i] * vals[j];
        }
    }
    //res.apply(sigmoid);

    res += _visibleBias;
}
/*
 This function trains the AE with SDG
 Input: The input to the AE
 Output:The RMSE value
 */
float AutoEncoder::train(valarray<float> input)
{

    std::valarray<float> res(_inputSize);
    std::valarray<float> hidden(_weights.size());

    getHiddenLayer(input,hidden);
    getVisibleLayer(hidden,res);

    valarray<float> tmp_visible(_inputSize);
    //update visible bias
    tmp_visible = input - res;
    _visibleBias += _learningRate * tmp_visible; //1 -N

    //update hidden bias
    valarray<float>tmp_hidden(_weights.size());
    for (int i = 0; i < _weights.size(); ++i) {
        tmp_hidden[i] = (_weights[i]*tmp_visible).sum();
    }
    tmp_hidden *= hidden*(1-hidden);

    _hiddenBias += _learningRate * tmp_hidden;//1 - N

    //update Weights
    for (int i = 0; i < _weights.size(); ++i)
    {
        for (int j = 0; j < _weights[i].size(); ++j)
        {
            _weights[i][j] = _learningRate * (tmp_hidden[i] *input[j] + tmp_visible[j] * res[i]);//1 -N
        }
    }


    return (input - res).sum();
}

