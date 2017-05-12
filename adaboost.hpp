#ifndef ADABOOST
#define ADABOOST

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

vector<pair<double, int> > strongClassifer(
    vector<pair<double, double> > h, int N, vector<vector<int> > validation);

#endif