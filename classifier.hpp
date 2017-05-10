#ifndef CLASSIFIER
#define CLASSIFIER

#include <iostream>
#include <vector>
#include <cstdlib>

#include "image.hpp"

std::vector<std::pair<double, double> > trainWeakClassifier(
    std::vector<Image> input, double alpha, double p);



#endif