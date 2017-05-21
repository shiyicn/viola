#include <iostream>
#include <vector>
#include "image.hpp"
#include "simpleClassifier.hpp"



int predict(Image & img,vector<SimpleClassifier>&strong, vector<double> &alpha,double theta);

int calTP(vector<Image> &imgs, vector<int> &results);
int calFP(vector<Image> &imgs, vector<int> &results);
int calTN(vector<Image> &imgs, vector<int> &results);
int calFN(vector<Image> &imgs, vector<int> &results);

pair<double,double> evaluate(Image &img,vector<SimpleClassifier> & strong, vector<double>&alpha,double theta);