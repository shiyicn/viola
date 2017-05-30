#ifndef CLASSIFIER
#define CLASSIFIER

#include <iostream>
#include <vector>
#include <cstdlib>

#include "image.hpp"
#include "simpleClassifier.hpp"

void trainWeakClassifier(SimpleClassifier & classifier, vector<Image> &images , double alpha, double p);
void getAllWeakClassifiers(vector<Image> &input, double alpha, double p, vector<SimpleClassifier> &cs);


vector<Image> load();

#endif
