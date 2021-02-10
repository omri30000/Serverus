//
// Created by Omri Zaiman on 04/02/2021.
//

#include "AnomalyDetector.h"

/*
AnomalyDetector class's constructor.
input:
 * numOfFeatures --> the amount of features in the input data set
 * amountToLearn --> the amount of instances to train the AD on before executing
 * learningRate --> the learningRate for all the auto encoders
 * hiddenLayerRatio --> the "beta" as represented in the article
 * featureMap --> the mapped features given from the FM
Output:
 * An object of AnomalyDetector
*/
AnomalyDetector::AnomalyDetector(int numOfFeatures, int amountToLearnFrom, float learningRate,
                                 float hiddenLayerRatio, vector<vector<float>> featuresMap) : _outputLayer(featuresMap.size(), learningRate)
{
    this->_featuresAmount = numOfFeatures;
    this->_amountToLearn = amountToLearnFrom;
    this->_learningRate = learningRate;
    this->_ratioOfHiddenLayer = hiddenLayerRatio;

    this->_trainedInstancesAmount = 0;
    this->_featuresMap = featuresMap;

    // initialize ensemble layer
    for (int i = 0; i < featuresMap.size(); i++) {
        this->_ensembleLayer.push_back(AutoEncoder(featuresMap[i].size(), learningRate));
    }
}

/*
The function ...
*/
float AnomalyDetector::perform(valarray<float> input)
{

}

/*
The function
*/
float AnomalyDetector::train(valarray<valarray<float>> input)
{
    return 0;
}

/*
the function will calculate an anomaly score to a specific packet
input: the mapped features of the specific packet
output: anomaly score of the packet
*/
float AnomalyDetector::calcAnomalyScore(valarray<valarray<float>> input)
{
    //create an empty array represents the input to the output layer
    valarray<float> inputOfOutputLayer(this->_ensembleLayer.size());

    for (int i = 0; i < inputOfOutputLayer.size(); i++) {
        inputOfOutputLayer[i] = this->_ensembleLayer[i].feedForward(input[i]);
    }

    return this->_outputLayer.feedForward(inputOfOutputLayer);
}