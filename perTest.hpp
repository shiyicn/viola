#include <iostream>
#include <vector>
#include "image.hpp"
#include "simpleClassifier.hpp"


/*------------------------------------------------
Make the prediction for a given image 
-------------------------------------------------*/
int predictMPI(Image & img,vector<SimpleClassifier>&strong, vector<double> &alpha);


/*------------------------------------------------
Get the value predicged, for comparing with threshhold
--------------------------------------------------*/
double  predictImage(Image & img, vector<SimpleClassifier> &strong, vector<double> &alpha);

/*-----------------------------------------------
Caculate the number of TP, FP, TN and FN 
------------------------------------------------*/
int calTP(vector<Image> &imgs, vector<int> &results);
int calFP(vector<Image> &imgs, vector<int> &results);
int calTN(vector<Image> &imgs, vector<int> &results);
int calFN(vector<Image> &imgs, vector<int> &results);

/*-----------------------------------------------
Caculate the number of TP, FP, TN and FN between result vector and sub true value vector
-------------------------------------------------*/
int gettpMPI(vector<Image>&imgs, vector<int> &results,int start,int end);
int getfpMPI(vector<Image>&imgs, vector<int> &results,int start,int end);
int gettnMPI(vector<Image>&imgs, vector<int> &results,int start,int end);
int getfnMPI(vector<Image>&imgs, vector<int> &results,int start,int end);

/*------------------------------------------------
Given a threshhold theta and test set, calculate the coordinate of the prediction result in ROC graph
--------------------------------------------------*/
pair<double,double>  evaluate(vector<Image> &imgs,vector<SimpleClassifier> & strong, vector<double>&alpha,double theta);

void evaluateROC(vector<Image> &imgs,vector<SimpleClassifier> &strong, vector<double>&alpha);