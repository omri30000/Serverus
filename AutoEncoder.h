//
// Created by ofir on 25/01/2021.
//

#include <valarray>

using std::valarray;


class AutoEncoder
{
protected:
    valarray<valarray<float>> _weights;
    valarray<float> _hiddenBias;
    valarray<float> _visibleBias;

    float _learningRate;
    int _inputSize;

    void getHiddenLayer(valarray<float>vals ,valarray<float>& res);
    void getVisibleLayer(valarray<float> vals,valarray<float>& res);

public:

    AutoEncoder(int inputSize,float learningRate);
    float train(valarray<float> input);
    float feedForward(valarray<float> input);
    float calcRmse(valarray<float> input,valarray<float> reconstruct);

};



