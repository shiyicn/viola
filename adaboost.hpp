#ifndef ADABOOST
#define ADABOOST

#include <iostream>
#include <vector>
#include <cstdlib>
#include <mpi.h>
#include "image.hpp"
#include "simpleClassifier.hpp"


using namespace std;

void strongClassifer(vector<Image> &valSet, vector<SimpleClassifier> &weaks, vector<SimpleClassifier>&strong, vector<double> &alpha, int N);

double errCal(SimpleClassifier & classifier, short c);
void getBestClassifier(double *lambda, vector<Image>& valSet, vector<SimpleClassifier> &classifiers, SimpleClassifier & best,double & err);            //get the classifier which get the best result

#endif