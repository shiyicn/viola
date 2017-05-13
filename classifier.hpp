#ifndef CLASSIFIER
#define CLASSIFIER

#include <iostream>
#include <vector>
#include <cstdlib>

#include "image.hpp"
#include "simpleClassifier.hpp"


vector<SimpleClassifier> trainWeakClassifier(vector<Image> input, double alpha, double p);
vector<Image> load();
void genDistFeature();

#endif