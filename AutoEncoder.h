//
// Created by ofir on 25/01/2021.
//

#include <valarray>

using std::valarray;

class AutoEncoder
{
    protected:
        valarray<float> _hiddenBias;
        valarray<float> _visibleBias;

        float _learningRate;
        int _inputSize;

        valarray<valarray<float>> _weights;

        void getHiddenLayer(valarray<float>vals ,valarray<float>& res);
        void getVisibleLayer(valarray<float> vals,valarray<float>& res);
        float calcRmse(valarray<float> input,valarray<float> reconstruct);

    public:
        AutoEncoder(int inputSize,float learningRate);

        float train(valarray<float> input);
        float feedForward(valarray<float> input);
};


