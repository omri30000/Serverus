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
        int _amountToLearn; // the number of instances that the component will learn from
        float _learningRate;
        float _ratioOfHiddenLayer; // the beta
        vector<AutoEncoder> _ensembleLayer;
        AutoEncoder _outputLayer;

        float train(valarray<float> input);
        float calcAnomalyScore(valarray<float> input);

    public:
        AnomalyDetector();
        ~AnomalyDetector() = default;

        float perform(valarray<float> input);
};

#endif //IDPS_20_21_ANOMALYDETECTOR_H
