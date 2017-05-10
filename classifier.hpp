#ifndef CLASSIFIER
#define CLASSIFIER

#include <iostream>
#include <vector>
#include <cstdlib>

#include "image.hpp"
#include "simpleClassifier.hpp"


std::vector<SimpleClassifier> trainWeakClassifier(
    std::vector<Image> input, double alpha, double p);



#endif