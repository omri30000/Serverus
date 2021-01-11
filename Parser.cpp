//
// Created by ofir on 11/01/2021.
//

#include "Parser.h"
//constructor
Parser::Parser(vector<vector<int>> order) {
    _order = order;
}

/*
 This function will parse the stats from FE to the correct orders in the AD
 input: stats : statistics from FE : vector<float>
 Output: data in correct order to the AD : vector<vector<float>>
 */
vector<vector<float>> Parser::organizeData(vector<float> stats) {
    vector<vector<float>> result;
    for (int i = 0; i < _order.size(); ++i) {
        result.push_back(std::vector<float>(_order[i].size()));
        for (int j = 0; j < _order[i].size(); ++j) {
            result[i][j] = stats[_order[i][j]];
        }
    }
    return result;
}


