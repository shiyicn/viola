#include "adaboost.hpp"

double errCal(Image & img,SimpleClassifier & classifier){
    return (classifier.predictByImage(img)==img.getImageClass())?0.0:1.0;
}

void getBestClassifier(vector<double> & lambda, vector<Image>& valSet, vector<SimpleClassifier> &classifiers, SimpleClassifier & best,double err){
    double minErr = numeric_limits<double>::infinity();
    int index=0;
    for(int i=0;i<classifiers.size();i++){
        double errCur = 0.0;
        for(int j=0;i<valSet.size();i++){
            errCur += lambda[j]*errCal(valSet[j],classifiers[j]);
        }
        if(err < minErr){
            index = i;
            minErr = errCur;
        }
    }
    best = classifiers[index];
    err = minErr;
}

void strongClassifier(vector<Image> &valSet, vector<SimpleClassifier> &weaks, vector<SimpleClassifier>&strong, vector<double> &alpha, int N){
    vector<double> lambda;
    double weightInit = 1.0/(double)valSet.size();
    for(int i=0;i<valSet.size();i++){               //initialize the weights
        lambda.push_back(weightInit);
    }
    for(int i=0;i<N;i++){
        SimpleClassifier best;
        double locErr;
        pair<double, int> err_rank;               //get the best classifier in this round and the rank of processus which contain this classifier
        getBestClassifier(lambda,valSet,weaks,best,localErr);
        MPI_Reduce(&pair<localErr,taskid>,err_rank,1,MPI_DOUBLE_INT,MPI_MAXLOC,root,root, MPI_COMM_WORLD);
        //**
        //not finished: 1,root brocast the id of the processus which have the best classifier in this round
        //              2,the processus which have the best classifier update the lambda and brocast to the other processus 
        //              end and run the next round
    

    }
}