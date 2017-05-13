#include "simpleClassifier.hpp"

SimpleClassifier::SimpleClassifier(double w_0,double w_1){
    this->w_0 = w_0;
    this->w_1 = w_1;
}

double SimpleClassifier::getW0(){
    return w_0;
}

double SimpleClassifier::getW1(){
    return w_1;
}

Type SimpleClassifier::getType(){
    return this->type;
}

Shape SimpleClassifier::getShape(){
    return this->shape;
}

Position SimpleClassifier::getPosition(){
    return this->position;
}

short SimpleClassifier::predict(Feature &f){
    this->type = f.getType();
    this->shape = f.getShape();
    this->position = f.getPosition();
    double predit = w_0 * f.getValue() + w_1;
    return (predit>=0)?1:-1;
}


