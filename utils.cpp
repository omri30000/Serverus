//
// Created by ofir on 29/01/2021.
//

#include <cmath>
#include "utils.h"
/*
 Return value from range with a uniform distribution
 Input:range : range of distribution
 output: value between the range
 */
float uniform(std::pair<float, float> range) {
    float val = rand() / (float)RAND_MAX;
    return range.first +val*(range.second - range.first);
}

/*
 This function performs a sigmoid function on a value
 Input: val - a float value
 Output: The sigmoid value of a nubmer
 */
float sigmoid(float val) {
    return 1/(1+exp(-val));
}

