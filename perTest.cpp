#include "perTest.hpp"

int predict(Image &img,vector<SimpleClassifier> & strong, vector<double>&alpha,double theta){
    double pre,term;
    for(int i=0;i<strong.size();i++){
        pre +=alpha[i]*strong[i].predictByImage(img);
        term +=alpha[i];
    }
    term *= theta;
    term -=1;
    if(pre >= term) return 1;
    else return -1;
}



int calTP(vector<Image> &imgs, vector<int> &results){
    int tp = 0;
    for(int i=0;i<imgs.size();i++){
        if((imgs[i].getImageClass()==1)&&(results[i]==1)) tp++;
    }
    return tp;
}

int calFP(vector<Image> &imgs, vector<int> &results){
    int fp = 0;
    for(int i=0;i<imgs.size();i++){
        if((imgs[i].getImageClass()==-1)&&(results[i]==1)) fp++;
    }
    return fp;
}

int calTN(vector<Image> &imgs, vector<int> &results){
    int tn = 0;
    for(int i=0;i<imgs.size();i++){
        if((imgs[i].getImageClass()==-1)&&(results[i]==-1)) tn++;
    }
    return tn;
}

int calFN(vector<Image> &imgs, vector<int> &results){
    int fn = 0;
    for(int i=0;i<imgs.size();i++){
        if((imgs[i].getImageClass()==1)&&(results[i]==-1)) fn++;
    }
    return fn;
}

pair<double,double> evaluate(vector<Image> &imgs,vector<SimpleClassifier> & strong, vector<double>&alpha,double theta){
    vector<int>result;
    int TP,FP,TN,FN;
    for(int i=0;i<imgs.size();i++){
        result.push_back(predict(imgs[i],strong,alpha,theta));
    }
    TP = calTP(imgs,result);
    FP = calFP(imgs,result);
    TN = calTN(imgs,result);
    FN = calFN(imgs,result);
    return make_pair((double)FP/(FP+TN),(double)TP/(TP+FN));
}