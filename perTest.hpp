#include <iostream>
#include <vector>
#include "image.hpp"
#include "simpleClassifier.hpp"


/*------------------------------------------------
Make the prediction for a given image 
-------------------------------------------------*/
int predict(Image & img,vector<SimpleClassifier>&strong, vector<double> &alpha,double theta);

/*-----------------------------------------------
Caculate the number of TP, FP, TN and FN 
------------------------------------------------*/
int calTP(vector<Image> &imgs, vector<int> &results);
int calFP(vector<Image> &imgs, vector<int> &results);
int calTN(vector<Image> &imgs, vector<int> &results);
int calFN(vector<Image> &imgs, vector<int> &results);

/*------------------------------------------------
Given a threshhold theta and test set, calculate the coordinate of the prediction result in ROC graph
--------------------------------------------------*/
pair<double,double>  evaluate(vector<Image> &imgs,vector<SimpleClassifier> & strong, vector<double>&alpha,double theta);