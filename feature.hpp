#ifndef FEATURE
#define FEATURE

#include <iostream>
#include <vector>
#include <cstdlib>
#include "util.hpp"

typedef unsigned short ushort;
enum Type {A,B,C,D};

class Feature{

    Type type;    //A,B,C,D
    Shape shape;   //size,
    Position position;       //position
    int value;              //the value caculated

    public:
        Feature(Type type, Shape s,Position p, const std::vector<std::vector<int> >& integral);
        int getValue();
        Type getType();
        Shape getShape();
        Position getPosition();
};

#endif
