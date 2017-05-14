#include "simpleClassifier.hpp"
#include "mpi.h"
#include <iostream>

SimpleClassifier::SimpleClassifier(double w_0,double w_1,int index){
    this->w_0 = w_0;
    this->w_1 = w_1;
    this->index = index;
}

double SimpleClassifier::getW0(){
    return w_0;
}

double SimpleClassifier::getW1(){
    return w_1;
}

void SimpleClassifier::setW0(double w){
    this->w_0 = w;
}

void SimpleClassifier::setW1(double w){
    this->w_1 = w;
}

/*Type SimpleClassifier::getType(){
    return 
}

Shape SimpleClassifier::getShape(){
    return this->shape;
}

Position SimpleClassifier::getPosition(){
    return this->position;
}*/

short SimpleClassifier::predictByFeature(Feature &f){
    //this->type = f.getType();
    //this->shape = f.getShape();
    //this->position = f.getPosition();
    double predit = w_0 * f.getValue() + w_1;
    return (predit>=0)?1:-1;
}

short SimpleClassifier::predictByImage(Image &img){
    Feature & f = img.getFeatureVector()[this->index];
    return this->predictByFeature(f);
}

void updatePara(Image &img, double alpha){
    short t = this->predictByImage(img)-img.getImageClass();
    int featureValue = img.getFeatureVector()[this->index].getValue();
    w_0 -= alpha*t*featureValue;
    w_1 -= alpha*t;
}


