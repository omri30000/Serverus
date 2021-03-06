//
// Created by ofir on 11/01/2021.
//

#include "../Headers/Parser.h"
//constructor
Parser::Parser(vector<vector<int>> order) {
    _order = order;
}

/*
 This function will parse the stats from FE to the correct orders in the AD
 input: stats : statistics from FE : vector<float>
 Output: data in correct order to the AD : vector<vector<float>>
 */
valarray<valarray<float>> Parser::organizeData(vector<float> stats) {
    valarray<valarray<float>> result(this->_order.size());

    for (int i = 0; i < _order.size(); ++i) {
        result[i] = valarray<float>(this->_order[i].size());

        for (int j = 0; j < _order[i].size(); ++j) {
            result[i][j] = stats[_order[i][j]];
        }
    }

    return result;
}


