//
// Created by ofir on 11/01/2021.
//
#pragma once

#include <vector>

using std::vector;

class Parser {
protected:
    vector<vector<int>> _order;

public:
    Parser(vector<vector<int>> order);

    vector<vector<float>> organizeData(vector<float> stats);
};
