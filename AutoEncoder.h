//
// Created by ofir on 25/01/2021.
//

#include <valarray>

using std::valarray;


class AutoEncoder
{
public:
    valarray<float> _hiddenBias;
    valarray<float> _visibleBias;

    float _learningRate;
    int _inputSize;

    void getHiddenLayer(valarray<float>vals ,valarray<float>& res);
    void getVisibleLayer(valarray<float> vals,valarray<float>& res);

    valarray<valarray<float>> _weights;

    AutoEncoder(int inputSize,float learningRate);
    float train(valarray<float> input);
    float feedForward(valarray<float> input);
    float calcRmse(valarray<float> input,valarray<float> reconstruct);

};



