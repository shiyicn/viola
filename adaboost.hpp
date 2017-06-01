#ifndef ADABOOST
#define ADABOOST

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <mpi.h>
#include "image.hpp"
#include "simpleClassifier.hpp"


using namespace std;

/*---------------------------------------------------------
Get the N best weak classifiers to form a strong classifier
# valSet : validation set
# weaks : vector of simpleclassifiers 
# strong : the strong classifier got 
# alpha : the alpha coefficient got 
# N : Number of simpleclassifiers 
----------------------------------------------------------*/
void strongClassifier(vector<Image> &valSet, vector<SimpleClassifier> &weaks, vector<SimpleClassifier>&strong, vector<double> &alpha, int N);

/*---------------------------------------------------------
Caculate the predict error of a classifier on some image
# img : the image on which the prediction is based 
# classifier : simple classifier 
----------------------------------------------------------*/
double errCal(Image & img, SimpleClassifier & classifier);

/*---------------------------------------------------------
In some round, given the weights lambda, get the best classifier which got the best performance in valSet 
# lambda : weights for images 
# valSet : validation set
# classifires : all the simpleclassifiers 
# best : the best simpleclassifier got in this round 
# err : the err caculated for this best classifier, used for updating lambda in the next round  
----------------------------------------------------------*/
void getBestClassifier(double *lambda, vector<Image>& valSet, vector<SimpleClassifier> &classifiers, SimpleClassifier & best,double err);            //get the classifier which get the best result


/*----------------------------------------------------------
Save the strong classifier got
# strongs : vector of simple classifiers chosed for storing 
# alpha : coeficients of these simpleclassiers chosed 
-----------------------------------------------------------*/
void saveClassifier(vector<SimpleClassifier>&strongs,vector<double>&alpha);

/*----------------------------------------------------------
Load the strong classifier from file 
-----------------------------------------------------------*/
void loadClassifier(vector<SimpleClassifier>&strongs, vector<double>&alpha);

#endif
