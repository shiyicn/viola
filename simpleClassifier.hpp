#ifndef SIMPLECLASSIFIER
#define SIMPLECLASSIFIER

typedef unsigned short ushort;

#include <vector>
#include <cstdlib>
#include "feature.hpp"

class SimpleClassifier{

    double w_0,w_1;
    ushort width,height;
    ushort x,y;

    public:
        SimpleClassifier(double w_0,double w_1);
        int calResult(Feature f);
}

#endif