//
// Created by Omri Zaiman on 04/02/2021.
//

#ifndef IDPS_20_21_ANOMALYDETECTOR_H
#define IDPS_20_21_ANOMALYDETECTOR_H

#include <vector>

#include "AutoEncoder.h"

using std::vector;

class AnomalyDetector {
    protected:
        int _featuresAmount; // the amount of features (received from FE -> 85)
        int _amountToLearn; // the number of instances that the component will learn from
        float _learningRate;
        float _ratioOfHiddenLayer; // the beta

        int _trainedInstancesAmount; // the amount of instances that has being trained

        vector<vector<float>> _featuresMap;

        vector<AutoEncoder> _ensembleLayer;
        AutoEncoder _outputLayer;

        void train(valarray<valarray<float>> input);
        float calcAnomalyScore(valarray<valarray<float>> input);

    public:
        AnomalyDetector(int numOfFeatures, int amountToLearnFrom,
                        float learningRate, float hiddenLayerRatio, vector<vector<float>> featuresMap);
        ~AnomalyDetector() = default;

        float perform(valarray<valarray<float>> input);
};

#endif //IDPS_20_21_ANOMALYDETECTOR_H
