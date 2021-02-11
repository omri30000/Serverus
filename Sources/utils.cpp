//
// Created by ofir on 29/01/2021.
//

#include <cmath>
#include "../Headers/utils.h"
/*
 Return value from range with a uniform distribution
 Input:range : range of distribution
 output: value between the range
 */
float uniform(std::pair<float, float> range) {
    float val = rand() / (float)RAND_MAX;
    val= range.first +val*(range.second - range.first+1);
    return val;
}

/*
 This function performs a sigmoid function on a value
 Input: val - a float value
 Output: The sigmoid value of a nubmer
 */
float sigmoid(float val) {
    float v=  1/(1+exp(-val));
    return v;
    }

int binomial(int n, double p)
{
    if(p < 0 || p > 1) return 0;

    int c = 0;
    double r;

    for(int i=0; i<n; i++) {
        r = rand() / (RAND_MAX + 1.0);
        if (r < p) c++;
    }

    return c;
}

