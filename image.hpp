#ifndef IMAGE
#define IMAGE

#include <iostream>
#include <vector>
#include <cstdlib>
#include "feature.hpp"

using namespace std;

class Image {
    vector<vector<int> > data;
    vector<vector<int> > integral;
    int c;

    Image(string fname, int c);

    vector<vector<int> > calIntegral(vector<vector<int> > image);
    vector<int> calFeatureVector(vector<vector<int> > integral, int incr, int size);
    
};

#endif