//
// Created by Omri Zaiman on 04/02/2021.
//

#include "../Headers/AnomalyDetector.h"
#include <iostream>
#include "math.h"
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
                                 float hiddenLayerRatio, vector<int> featuresMap) : _outputLayer(featuresMap.size(), learningRate)
{
    this->_featuresAmount = numOfFeatures;
    this->_amountToLearn = amountToLearnFrom;
    this->_learningRate = learningRate;
    this->_ratioOfHiddenLayer = hiddenLayerRatio;

    this->_trainedInstancesAmount = 0;

    // initialize ensemble layer
    for (int i = 0; i < featuresMap.size(); i++) {
        this->_ensembleLayer.push_back(AutoEncoder(featuresMap[i], learningRate));
    }
}

/*
The function will make sure that the AnomalyDetector will be created only once
 input:
 * numOfFeatures --> the amount of features in the input data set
 * amountToLearn --> the amount of instances to train the AD on before executing
 * learningRate --> the learningRate for all the auto encoders
 * hiddenLayerRatio --> the "beta" as represented in the article
 * featureMap --> the mapped features given from the FM
Output:
 * An object of AnomalyDetector
*/
AnomalyDetector& AnomalyDetector::getInstance(int numOfFeatures, int amountToLearnFrom,
                                    float learningRate, float hiddenLayerRatio, vector<int> featuresMap)
{
    static AnomalyDetector instance(numOfFeatures, amountToLearnFrom,
                                    learningRate, hiddenLayerRatio, featuresMap);

    return instance;
}



/*
The function will train the model and calc the anomaly score during training (not for use)
input: the mapped features of a specific packet
output: anomaly score of the packet (meaningless)
*/
float AnomalyDetector::train(valarray<valarray<float>> input)
{
    //create an empty array represents the input to the output layer
    valarray<float> inputOfOutputLayer(this->_ensembleLayer.size());

    for (int i = 0; i < inputOfOutputLayer.size(); i++) {
        inputOfOutputLayer[i] = this->_ensembleLayer[i].train(input[i]);

    }
    this->_trainedInstancesAmount++;

   return this->_outputLayer.train(inputOfOutputLayer);

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
/*
The function will check weather the AD should perform training or execution and perform the action
input: the mapped features of a specific packet
output: std::pair- {anomaly score of the packet (meaningless), is the train finished}
*/

}
std::pair<float, bool> AnomalyDetector::perform(valarray<valarray<float>> input)
{
    float anomalyScore = 0;
    bool isTrain= this->_trainedInstancesAmount <=  this->_amountToLearn;

    if(isTrain)
    {
        anomalyScore = this->train(input);
        //no score before 100 batches
        anomalyScore = this->_trainedInstancesAmount > 100 ? anomalyScore : 0;
        std::cout<<"train: "<<anomalyScore<<std::endl;
    }
    else
    {
        anomalyScore = this->calcAnomalyScore(input);
    }

    return{anomalyScore,isTrain} ;
}
