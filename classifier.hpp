#ifndef CLASSIFIER
#define CLASSIFIER

#include <iostream>
#include <vector>
#include <cstdlib>

#include "image.hpp"
#include "simpleClassifier.hpp"

<<<<<<< HEAD

std::vector<SimpleClassifier> trainWeakClassifier(std::vector<Image> input, double alpha, double p);


=======
vector<pair<double, double> > trainWeakClassifier(
    vector<Image> input, double alpha, double p);
>>>>>>> 5b157012570a859f347d2c45909ff6a3dad64fa9

#endif