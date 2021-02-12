//
// Created by ofir on 11/01/2021.
//
#pragma once

#include <vector>
#include <valarray>

using std::vector;
using std::valarray;

class Parser {
protected:
    vector<vector<int>> _order;

public:
    Parser(vector<vector<int>> order);

    valarray<valarray<float>> organizeData(vector<float> stats);
};
