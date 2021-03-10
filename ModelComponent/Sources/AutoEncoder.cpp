//
// Created by ofir on 25/01/2021.
//

#include <iostream>
#include "../Headers/AutoEncoder.h"
#include "../Headers/utils.h"
//void printValAraay(valarray<float> t);
//constructor
AutoEncoder::AutoEncoder(int inputSize,float learningRate =0.1)
{


    _inputSize = inputSize;
    float b = 1;

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

    normMax = valarray<float>(-std::numeric_limits<float>::infinity(),inputSize);
    normMin = valarray<float>(std::numeric_limits<float>::infinity(),inputSize);


}

/*
 This function calculates the RMSE value for an input
 Input: input to the AE : valarray<float>
 Output: The RMSE value
 */
float AutoEncoder::feedForward(valarray<float> input)
{
    //norm(input,false);
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
float AutoEncoder::calcRmse(valarray<float> input,valarray<float> reconstruct)  const
{
    valarray<float>  v = std::pow(input- reconstruct,2);
    return sqrt(v.sum() / v.size());
}
/*
 This function returns the Hidden Layer - The second layer (feed forward)
 Input:vals : the input to the AE
       res: refrence to the hidden layer values
  Output :None
 */
void AutoEncoder::getHiddenLayer(valarray<float> vals, valarray<float> &res) const
{
    for (int i = 0; i < _weights.size(); ++i)
    {
        res[i] = (vals * _weights[i]).sum();
    }
    res += _hiddenBias;
    res= res.apply(sigmoid);
}
/*
 This function returns the Visible Layer - The third layer (feed forward)
 Input:vals : the input to the AE
       res: refrence to the visible layer values
  Output :None
 */
void AutoEncoder::getVisibleLayer(valarray<float> vals, valarray<float> &res) const
{
    for (int i = 0; i < _inputSize; ++i)
    {
        res[i] = 0;
        for (int j = 0; j < _weights.size(); ++j)
        {
            res[i] += _weights[j][i] * vals[j];
        }
    }
    res += _visibleBias;
    res = res.apply(sigmoid);
}
/*
 This function trains the AE with SDG
 Input: The input to the AE
 Output:The RMSE value
 */
float AutoEncoder::train(valarray<float> input)
{
    //norm(input,true);
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
            _weights[i][j] += _learningRate * (tmp_hidden[i] *input[j] + tmp_visible[j] * res[i]);
        }
    }

    //std::cout<<"dif: "<<(input-res).sum()<<std::endl;//<std::endl<<"rmse: ";
    return calcRmse(input,res);
}

void AutoEncoder::norm(valarray<float> &vals,bool isLearning)
{
    if(isLearning)
    {
        for (int i = 0; i < vals.size(); ++i) {
            normMax[i] = std::max(normMax[i], vals[i]);
            normMin[i] = std::min(normMin[i], vals[i]);
        }
    }
    vals = (vals-normMin) / (normMax - normMin + 0.00000000001);

}


/*
//for debug use only

int main(void) {
    srand(0);

    double learning_rate = 0.1;
    double corruption_level = 0.3;
    int training_epochs = 100;

    int train_N = 10;
    int test_N = 2;
    int n_visible = 20;
    int n_hidden = 5;

    // training data
    valarray<valarray<float>> train_X = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0}
    };

    for (int i = 0; i < train_X.size(); ++i)
    {
        for (int j = 0; j < train_X[i].size(); ++j)
        {
            if(train_X[i][j] != 0)
                train_X[i][j] = binomial(1,0.7);
        }
    }

    // construct dA
    AutoEncoder da(n_visible,0.1);

    // train
    for (int epoch = 0; epoch < 20; epoch++) {
        for (int i = 0; i < train_N; ++i) {
            std::cout<<da.train(train_X[i])<<std::endl;

        }

    }
    for (int i = 0; i < da._weights.size(); ++i)
    {
        for (int j = 0; j < da._weights[i].size(); ++j) {
            //std::cout << da._weights[i][j] << ", ";
        }
//        std::cout << std::endl;
    }

    valarray<valarray<float>> test_X = {
            {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0}
    };
    for (int i = 0; i < 2; ++i) {
        std::cout<<da.feedForward(test_X[i])<<std::endl;
    }


}

void printValAraay(valarray<float> t)
{
    //std::cout<<t.sum();

    for (int j = 0; j < t.size() ;++j)
    {
        //std::cout << t[j] << ", ";
    }
    std::cout<<std::endl<< "======================"<<std::endl ;

}
*/