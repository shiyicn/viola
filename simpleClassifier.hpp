#ifndef SIMPLECLASSIFIER
#define SIMPLECLASSIFIER

typedef unsigned short ushort;

#include <vector>
#include <cstdlib>
#include "feature.hpp"

class SimpleClassifier{

    double w_0,w_1;
    Type type;
    Shape shape;
    Position position;
    

    public:
        SimpleClassifier(double w_0,double w_1);
        short predict(Feature &f);
        double getW0();
        double getW1();
        Type getType();
        Shape getShape();
        Position getPosition();
};

#endif