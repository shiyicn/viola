#ifndef CLASSIFIER
#define CLASSIFIER

#include <iostream>
#include <vector>
#include <cstdlib>

#include "image.hpp"
#include "simpleClassifier.hpp"

vector<pair<double, double> > trainWeakClassifier(
    vector<Image> input, double alpha, double p);

#endif