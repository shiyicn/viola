#ifndef ADABOOST
#define ADABOOST

#include <iostream>
#include <vector>
#include <cstdlib>

std::vector<std::pair<double, int> > strongClassifer(
    std::vector<std::pair<double, double> > h, int N, std::vector<std::vector<int> > validation);

#endif